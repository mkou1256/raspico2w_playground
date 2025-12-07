#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "typedef.h"
#include "dbg_print.h"
#include "usb_comm.h"

int8_t systemInit()
{
    // stdioの初期化
    if (!stdio_init_all()) {
        return E_INIT;
    }

    // Wi-Fiチップの初期化
    if (cyw43_arch_init()) {
        return E_INIT;
    }

    // USB通信の初期化
    // USB通信に用いるリングバッファの初期化も含む
    if (usbCommInit() != E_SUCCESS) {
        return E_INIT;
    }

    return E_SUCCESS;
}

int main() {

    // システム初期化
    if (systemInit() != E_SUCCESS) {
        return -1;
    }

    while (true) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);  // LED ON
        sleep_ms(1000);

        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);  // LED OFF
        sleep_ms(1000);

        dbgPrint(DBG_LEVEL_DEBUG, "This is a debug message.\r\n");
        dbgPrint(DBG_LEVEL_INFO, "This is an info message.\r\n");
        dbgPrint(DBG_LEVEL_WARN, "This is a warning message.\r\n");
        dbgPrint(DBG_LEVEL_ERROR, "This is an error message.\r\n");
    }
}
