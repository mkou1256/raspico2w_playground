#include "usb_comm.h"

#include <stdint.h>

#include "dbg_print.h"
#include "ring_buffer.h"
#include "rtos_wrapper.h"
#include "typedef.h"

/****************************************************
 * static resource
 ****************************************************/
#define USB_TX_BUFFER_SIZE 1024
#define USB_RX_BUFFER_SIZE 256
static uint8_t s_usbTxBuffer[USB_TX_BUFFER_SIZE]; // リングバッファーに使用
static uint8_t s_usbRxBuffer[USB_RX_BUFFER_SIZE];
ringBuffer_t s_usbTxRingBuffer;

// タスク間同期用フラグ
// 送信: リングバッファに入れたらフラッグを立てる
rtos_static_flag_buf_t flag_buf_usbFlush;
rtos_flag_t flag_usbFlush = NULL;
// 受信: コールバックでフラッグを立てる
rtos_static_flag_buf_t flag_buf_usbDrain;
rtos_flag_t flag_usbDrain = NULL;

// 受信アプリケーションへの伝達用Queue
// 各アプリケーションでqueueを作成し、registerUsbRxQueue()で登録する
static usbRxData_t s_usbRxData; // 受信データ格納用構造体
#define MAX_USBRX_APP_QUEUE 4
usbRxQueue_t s_usbRxAppQueues[MAX_USBRX_APP_QUEUE];

/****************************************************
 * Init Proc
 ****************************************************/
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
    if (ringBufferInit(&s_usbTxRingBuffer, s_usbTxBuffer, USB_TX_BUFFER_SIZE) !=
        E_SUCCESS)
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

    initUsbRxAppQueues();

    init = 1;
    return E_SUCCESS;
}

/****************************************************
 * USB TX
 *  1. UsbTxが呼ばれたら、RingBufferにデータ格納
 *  2. データ格納時にタスク通知
 *  3. usbFlush_taskで格納されたデータを送信
 ****************************************************/
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

int32_t usbFlush()
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
        rtos_bit_t bit =
            rtos_flag_wait(flag_usbFlush, BIT_0, TRUE, FALSE, MAX_DELAY);
        usbFlush();
    }
}

/****************************************************
 * USB RX
 *  1. USB Bufferにデータが来たらコールバックでタスク通知
 *  2. usbDrain_taskでデータを取り出す
 *  3. 登録されたアプリケーションQueueにデータを格納
 ****************************************************/
int8_t makeRxData(const uint8_t *data, size_t len)
{
    memset(&s_usbRxData, 0, sizeof(usbRxData_t));
    s_usbRxData.id = 0;
    s_usbRxData.dataLen = len;
    memcpy(s_usbRxData.data, data, len);

    return E_SUCCESS;
}

int8_t enqueueUsbRxData_App(usbRxData_t *p_data)
{
    for (int i = 0; i < MAX_USBRX_APP_QUEUE; i++)
    {
        if (s_usbRxAppQueues[i].registered == 1)
        {
            rtos_queue_t queue = *(s_usbRxAppQueues[i].p_appQueue);
            if (rtos_queue_send(queue, (void *)p_data, 0) == RTOS_OK)
            {
                return E_SUCCESS;
            }
        }
        return E_OTHER;
    }
}

rtos_task_func_t usbDrain_task(void *params)
{
    while (1)
    {
        rtos_bit_t bit =
            rtos_flag_wait(flag_usbDrain, BIT_0, TRUE, FALSE, MAX_DELAY);
        int read = stdio_usb_in_chars(s_usbRxBuffer, USB_RX_BUFFER_SIZE);
        if (read <= 0)
        {
            dbgPrint(DBG_LEVEL_WARN, "[usbDrain_task] No data received\n");
            continue;
        }

        read = (read > USBRX_DATA_MAX_SIZE) ? USBRX_DATA_MAX_SIZE : read;
        if (makeRxData(s_usbRxBuffer, read) != E_SUCCESS)
        {
            dbgPrint(DBG_LEVEL_ERROR,
                     "[usbDrain_task] Failed to make RxData\n");
            continue;
        }

        if (enqueueUsbRxData_App(&s_usbRxData) != E_SUCCESS)
        {
            dbgPrint(
                DBG_LEVEL_WARN,
                "[usbDrain_task] No app queue registered or enqueue failed\n");
            continue;
        }
    }
}

void usbRecv_callback(void *params)
{
    rtos_bit_t bit = rtos_flag_set(flag_usbDrain, BIT_0);
}

void initUsbRxAppQueues()
{
    for (int i = 0; i < MAX_USBRX_APP_QUEUE; i++)
    {
        s_usbRxAppQueues[i].p_appQueue = NULL;
        s_usbRxAppQueues[i].registered = 0;
    }
}

int8_t registerUsbRxQueue(rtos_queue_t *p_appQueue)
{
    if (p_appQueue == NULL)
    {
        return E_ARGUMENT;
    }

    for (int i = 0; i < MAX_USBRX_APP_QUEUE; i++)
    {
        if (s_usbRxAppQueues[i].registered == 0)
        {
            s_usbRxAppQueues[i].p_appQueue = p_appQueue;
            s_usbRxAppQueues[i].registered = 1;
            return E_SUCCESS;
        }
    }
    return E_NO_RESOURCE;
}