#ifndef __USB_COMM__
#define __USB_COMM__

#include "rtos_wrapper.h"
#include "typedef.h"

extern int32_t usbCommInit();
extern int32_t usbBufferEnqueue(const char *str, size_t len);
extern int32_t usbFlushTxBuffer();
extern int32_t usbTx(const char *str, size_t len);
extern rtos_task_func_t usbFlush_task(void *params);
extern rtos_task_func_t usbDrain_task(void *params);
extern void usbRecv_callback(void *params);

#endif // __USB_COMM__
