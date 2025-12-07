#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "typedef.h"
#include "dbg_print.h"
#include "usb_comm.h"
#include "task_test.h" // test
#include "FreeRTOS.h"
#include "task.h"

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

    BaseType_t ret = xTaskCreate(
        task1,    // タスク関数
        "Task1",          // タスク名
        256,              // スタックサイズ
        NULL,             // パラメータ
        1,                // 優先度
        NULL              // タスクハンドル
    );
    if (ret != pdPASS) {
        dbgPrint(DBG_LEVEL_ERROR, "Failed to create Task1\r\n");
        return -1;
    }

    ret = xTaskCreate(
        task2,    // タスク関数
        "Task2",          // タスク名
        256,              // スタックサイズ
        NULL,             // パラメータ
        1,                // 優先度
        NULL              // タスクハンドル
    );
    if (ret != pdPASS) {
        dbgPrint(DBG_LEVEL_ERROR, "Failed to create Task2\r\n");
        return -1;
    }

    dbgPrint(DBG_LEVEL_INFO, "Starting scheduler...\r\n");
    vTaskStartScheduler();

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
