#include "task_test.h"
#include "dbg_print.h"
#include "pico/stdlib.h"
#include "rtos_wrapper.h"

void task1(void* pvParameters)
{
    static uint32_t count = 0;
    while (1) {
        dbgPrint(DBG_LEVEL_INFO, "Task 1 is running. %d\r\n", count++);
        rtos_task_delay(1000);
    }
}

void task2(void* pvParameters)
{
    static uint32_t count = 0;
    while (1) {
        dbgPrint(DBG_LEVEL_WARN, "Task 2 is running. %d\r\n", count++);
        rtos_task_delay(500);
    }
}
