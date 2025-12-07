#include "task_test.h"
#include "dbg_print.h"
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"

void task1(void* pvParameters)
{
    static uint32_t count = 0;
    while (1) {
        dbgPrint(DBG_LEVEL_INFO, "Task 1 is running. %d\r\n", count++);
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

void task2(void* pvParameters)
{
    static uint32_t count = 0;
    while (1) {
        dbgPrint(DBG_LEVEL_WARN, "Task 2 is running. %d\r\n", count++);
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}