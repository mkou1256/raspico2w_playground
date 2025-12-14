#include "usb_comm.h"
#include "typedef.h"
#include "ring_buffer.h"

#define USB_TX_BUFFER_SIZE  1024
#define USB_RX_BUFFER_SIZE  1024
static uint8_t s_usbTxBuffer[USB_TX_BUFFER_SIZE];
static uint8_t s_usbRxBuffer[USB_RX_BUFFER_SIZE];
ringBuffer_t s_usbTxRingBuffer;
ringBuffer_t s_usbRxRingBuffer;

int32_t usbCommInit()
{
    if (!stdio_usb_init()) {
        return E_INIT;
    }

    // リングバッファの初期化
    if (ringBufferInit(&s_usbTxRingBuffer, s_usbTxBuffer, USB_TX_BUFFER_SIZE) != E_SUCCESS) {
        return E_INIT;
    }
    if (ringBufferInit(&s_usbRxRingBuffer, s_usbRxBuffer, USB_RX_BUFFER_SIZE) != E_SUCCESS) {
        return E_INIT;
    }
    
    return E_SUCCESS;
}

int32_t usbBufferEnqueue(const char* str, size_t len)
{
    if (str == NULL || len == 0) {
        return 0;
    }

    ringBuffer_t* pRb = &s_usbTxRingBuffer;
    return ringBufferEnqueue(pRb, (const uint8_t*)str, len);
}

int32_t usbFlushTxBuffer()
{
    int32_t ret = E_OTHER;
    ringBuffer_t* pRb = &s_usbTxRingBuffer;
    uint8_t workBuffer[USB_TX_BUFFER_SIZE];

    int32_t len = ringBufferDequeue(pRb, workBuffer, USB_TX_BUFFER_SIZE);
    if (len > 0) {
        ret = stdio_put_string((const char*)workBuffer, len, false, false);
        // TODO: 低レベルAPIに変更
        if (ret < 0) {
            ret = E_USBCOMM;
        }                                                                

    }
    return ret;
}

int32_t usbTx(const char* str, size_t len)
{
    int32_t totalSent = 0;
    int32_t ret = E_OTHER;
    while (totalSent < len) {
        ret = usbBufferEnqueue(str + totalSent, len - totalSent);
        if (ret < 0) {
            return ret; // エラー
        }
        totalSent += ret;

        ret = usbFlushTxBuffer();
        if (ret < 0) {
            return ret; // エラー
        }
    }
    return totalSent;
}
