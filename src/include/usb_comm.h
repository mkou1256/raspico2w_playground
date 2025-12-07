#ifndef __USB_COMM__
#define __USB_COMM__

#include "pico/stdlib.h"

extern int32_t usbCommInit();
extern int32_t usbBufferEnqueue(const char* str, size_t len);
extern int32_t usbFlashTxBuffer();
extern int32_t usbTx(const char* str, size_t len);

#endif // __USB_COMM__