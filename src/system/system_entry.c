#include "dbg_print.h"
#include "rtos_wrapper.h"
#include "system_init.h"
#include "task_test.h" // test
#include "typedef.h"

/****************************************************
 * forward declaration
 ****************************************************/
int main();

int main()
{

    // システム初期化
    if (systemInit() != E_SUCCESS)
    {
        return -1;
    }

    rtos_result_t res = rtos_task_create(task1, "task1", 512, NULL, 1, NULL);

    res = rtos_task_create(task2, "task2", 512, NULL, 1, NULL);

    dbgPrint(DBG_LEVEL_INFO, "Starting scheduler...\r\n");
    rtos_schedule_start();
    // TODO: Assert;
}
