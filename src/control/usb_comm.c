#include "usb_comm.h"

#include <stdint.h>

#include "dbg_print.h"
#include "ring_buffer.h"
#include "rtos_wrapper.h"
#include "typedef.h"

#define USB_TX_BUFFER_SIZE 1024
#define USB_RX_BUFFER_SIZE 1024
static uint8_t s_usbTxBuffer[USB_TX_BUFFER_SIZE];
static uint8_t s_usbRxBuffer[USB_RX_BUFFER_SIZE];
ringBuffer_t s_usbTxRingBuffer;
ringBuffer_t s_usbRxRingBuffer;

rtos_static_flag_buf_t flag_buf_usbFlush;
rtos_flag_t flag_usbFlush = NULL;

rtos_static_flag_buf_t flag_buf_usbDrain;
rtos_flag_t flag_usbDrain = NULL;

int32_t usbCommInit()
{
    static int8_t init = 0;
    if (init == 1)
    {
        return E_SUCCESS;
    }
    if (!stdio_usb_init())
    {
        return E_INIT;
    }

    // リングバッファの初期化
    if (ringBufferInit(&s_usbTxRingBuffer, s_usbTxBuffer, USB_TX_BUFFER_SIZE) != E_SUCCESS)
    {
        return E_INIT;
    }
    if (ringBufferInit(&s_usbRxRingBuffer, s_usbRxBuffer, USB_RX_BUFFER_SIZE) != E_SUCCESS)
    {
        return E_INIT;
    }

    flag_usbFlush = rtos_flag_create_static(&flag_buf_usbFlush);
    if (flag_usbFlush == NULL)
    {
        return E_INIT;
    }

    flag_usbDrain = rtos_flag_create_static(&flag_buf_usbDrain);
    if (flag_usbDrain == NULL)
    {
        return E_INIT;
    }

    stdio_set_chars_available_callback(usbRecv_callback, NULL);

    init = 1;
    return E_SUCCESS;
}

int32_t usbBufferEnqueue(const char *str, size_t len)
{
    if (str == NULL || len == 0)
    {
        return 0;
    }

    ringBuffer_t *pRb = &s_usbTxRingBuffer;
    int32_t ret = ringBufferEnqueue(pRb, (const uint8_t *)str, len);

    rtos_bit_t bit = rtos_flag_set(flag_usbFlush, BIT_0);

    return ret;
}

int32_t usbFlushTxBuffer()
{
    int32_t ret = E_OTHER;
    ringBuffer_t *pRb = &s_usbTxRingBuffer;
    uint8_t workBuffer[USB_TX_BUFFER_SIZE];

    int32_t len = ringBufferDequeue(pRb, workBuffer, USB_TX_BUFFER_SIZE);
    if (len > 0)
    {
        ret = stdio_put_string((const char *)workBuffer, len, false, false);
        // TODO: 低レベルAPIに変更
        if (ret < 0)
        {
            ret = E_USBCOMM;
        }
    }
    return ret;
}

int32_t usbTx(const char *str, size_t len)
{
    int32_t totalSent = 0;
    int32_t ret = E_OTHER;
    while (totalSent < len)
    {
        ret = usbBufferEnqueue(str + totalSent, len - totalSent);
        if (ret < 0)
        {
            return ret; // エラー
        }
        totalSent += ret;
    }
    return totalSent;
}

rtos_task_func_t usbFlush_task(void *params)
{
    while (1)
    {
        rtos_bit_t bit = rtos_flag_wait(flag_usbFlush, BIT_0, TRUE, FALSE, MAX_DELAY);
        usbFlushTxBuffer();
    }
}

rtos_task_func_t usbDrain_task(void *params)
{
    uint8_t buffer[256];
    while (1)
    {
        rtos_bit_t bit = rtos_flag_wait(flag_usbDrain, BIT_0, TRUE, FALSE, MAX_DELAY);
        printf("XXX");
        int read = stdio_usb_in_chars(buffer, 256);
    }
}

void usbRecv_callback(void *params)
{
    rtos_bit_t bit = rtos_flag_set(flag_usbDrain, BIT_0);
}
