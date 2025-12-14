#ifndef __TYPEDEF__
#define __TYPEDEF__

// 共通ヘッダー
#include "pico/cyw43_arch.h"
#include "pico/stdio_usb.h"
#include "pico/stdlib.h"
#include <stdint.h>
#include <string.h>

// Common return values
#define E_SUCCESS 0
#define E_INIT -1
#define E_TIMEOUT -2
#define E_ARGUMENT -3
#define E_BUFSIZE -4
#define E_USBCOMM -5
#define E_OTHER -99

// BIT
#define BIT_0 (1 << 0)
#define BIT_1 (1 << 1)
#define BIT_2 (1 << 2)
#define BIT_3 (1 << 3)

// Logic
#define TRUE (1)
#define FALSE (0)

#endif // __TYPEDEF__
