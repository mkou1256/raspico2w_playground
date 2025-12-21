#ifndef __USB_COMM__
#define __USB_COMM__

#include "rtos_wrapper.h"
#include "typedef.h"

// USB受信データ格納用構造体
// この構造体のポインタをQueueでアプリケーションに渡す
#define USBRX_DATA_MAX_SIZE 32 // 受信したら即座にキューに積むので小さくてよい
typedef struct
{
    uint8_t id;                        // データ識別ID(今のところ未使用)
    size_t dataLen;                    // データ長
    uint8_t data[USBRX_DATA_MAX_SIZE]; // 実際のデータ
} usbRxData_t;

// アプリケーションがデータを受信するためのQueue登録用構造体
// usbRxData_tのポインタを、p_appQueueで受け渡す
typedef struct
{
    rtos_queue_t *p_appQueue; // アプリケーション側のQueueポインタ
    int8_t registered;        // 登録済みフラグ: 0->未登録, 1->登録済み
} usbRxQueue_t;

extern int32_t usbCommInit();
extern int32_t usbBufferEnqueue(const char *str, size_t len);
extern int32_t usbFlush();
extern int32_t usbTx(const char *str, size_t len);
extern void usbRecv_callback(void *params);

#endif // __USB_COMM__
