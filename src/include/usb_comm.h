#ifndef __USB_COMM__
#define __USB_COMM__

#include "pico/stdlib.h"

extern int32_t usbCommInit();
extern int32_t usbBufferTx(const char* str, size_t len);
extern int32_t usbFlashTxBuffer();

#endif // __USB_COMM__