#include "task_test.h"
#include "dbg_print.h"
#include "pico/stdlib.h"
#include "rtos_wrapper.h"
#include "usb_comm.h"

/****************************************************
 * forward declaration
 ****************************************************/
void task1(void *pvParameters);
void task2(void *pvParameters);

void task1(void *pvParameters)
{
    static uint32_t count = 0;
    while (1)
    {
        dbgPrint(DBG_LEVEL_INFO, "Task 1 is running. %d\r\n", count++);
        rtos_task_delay(1000);
    }
}

static rtos_queue_t s_testQueue = NULL;
void task2(void *pvParameters)
{
    s_testQueue = rtos_queue_create(10, sizeof(usbRxData_t));
    int8_t res_reg = registerUsbRxQueue(&s_testQueue);
    if (res_reg != E_SUCCESS)
    {
        dbgPrint(DBG_LEVEL_ERROR,
                 "Failed to register USB Rx Queue in Task 2\r\n");
    }

    rtos_result_t res_dequeue;
    usbRxData_t rxData;
    uint8_t command_buf[64] = {0};
    uint8_t *pbuf = command_buf;
    size_t len = 0;

    while (1)
    {
        res_dequeue = rtos_queue_receive(s_testQueue, &rxData, MAX_DELAY);
        if (res_dequeue != RTOS_OK)
        {
            dbgPrint(DBG_LEVEL_ERROR,
                     "Task 2: Failed to receive from USB Rx Queue\r\n");
            continue;
        }

        // 一文字ずつバッファーに貯めていく
        for (int i = 0; i < rxData.dataLen; i++)
        {
            if (rxData.data[i] == '\r')
            {
                // '\r'は処理しない。
                // len, pbufともに更新しないでcontinue
                continue;
            }

            if (rxData.data[i] == '\n')
            {
                // '\n'で区切りとみなす
                dbgPrint(DBG_LEVEL_INFO, "Task 2: command received: %s\r\n",
                         command_buf);
                memset(command_buf, 0, sizeof(command_buf));
                len = 0;
                pbuf = command_buf;
                continue;
            }

            // バッファーオーバーフロー対策
            if (len > sizeof(command_buf) - 1)
            {
                dbgPrint(DBG_LEVEL_WARN, "Task 2: command too long\r\n");
                memset(command_buf, 0, sizeof(command_buf));
                len = 0;
                pbuf = command_buf;
                continue;
            }

            // そのほかの場合はバッファーに一文字ずつ追加
            memcpy(pbuf, &rxData.data[i], 1);
            pbuf++;
            len++;
        }
    }
}
