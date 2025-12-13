#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "typedef.h"
#include "system_init.h"
#include "dbg_print.h"
#include "task_test.h" // test
#include "FreeRTOS.h"
#include "task.h"


int main() {

    // システム初期化
    if (systemInit() != E_SUCCESS) {
        return -1;
    }

    BaseType_t ret = xTaskCreate(
        task1,    // タスク関数
        "Task1",          // タスク名
        512,              // スタックサイズ
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
        512,              // スタックサイズ
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
    // TODO: Assert;
}
