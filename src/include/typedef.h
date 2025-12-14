#ifndef __TYPEDEF__
#define __TYPEDEF__

// 共通ヘッダー
#include <stdint.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/stdio_usb.h"
#include "pico/cyw43_arch.h"

// Common return values
#define E_SUCCESS       0
#define E_INIT         -1
#define E_TIMEOUT      -2
#define E_ARGUMENT     -3
#define E_BUFSIZE      -4
#define E_USBCOMM      -5
#define E_OTHER        -99

#endif // __TYPEDEF__
