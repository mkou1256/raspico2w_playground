#ifndef RTOS_WRAPPER_H
#define RTOS_WRAPPER_H

#include "FreeRTOS.h"
#include "event_groups.h"
#include "portmacrocommon.h"
#include "semphr.h"
#include "task.h"
#include <stdint.h>

/****************************************************
 * Type Definitions
 ****************************************************/
// base type
typedef int32_t rtos_base_t;
typedef uint32_t rtos_ubase_t;
typedef enum
{
    RTOS_OK = 0,
    RTOS_ERROR = -1,
    RTOS_TIMEOUT = -2
} rtos_result_t;
typedef uint64_t rtos_time_ms_t;
#define MAX_DELAY portMAX_DELAY

// task
typedef TaskHandle_t rtos_task_handle_t;
typedef TaskFunction_t rtos_task_func_t;
typedef TaskStatus_t rtos_task_status_t;
typedef configSTACK_DEPTH_TYPE rtos_stack_size_t;
typedef StackType_t rtos_stack_t;
typedef StaticTask_t rtos_tcb_t;
typedef UBaseType_t rtos_priority_t;

// mutex
typedef SemaphoreHandle_t rtos_mutex_t;
typedef StaticSemaphore_t rtos_static_mutex_buf_t;

// flag
typedef EventGroupHandle_t rtos_flag_t;
typedef EventBits_t rtos_bit_t;
typedef StaticEventGroup_t rtos_static_flag_buf_t;

// queue
typedef QueueHandle_t rtos_queue_t;
typedef StaticQueue_t rtos_static_queue_buf_t;
typedef UBaseType_t rtos_queue_size_t;

/******************************************************************************
 * Priority Constants
 ******************************************************************************/

#define RTOS_PRIORITY_IDLE 0
#define RTOS_PRIORITY_LOW 1
#define RTOS_PRIORITY_NORMAL 2
#define RTOS_PRIORITY_HIGH 3

/****************************************************
 * Task API
 ****************************************************/

rtos_result_t rtos_task_create(rtos_task_func_t func, const char *name,
                               rtos_stack_size_t stack_size, void *params,
                               rtos_priority_t priority,
                               rtos_task_handle_t *handle);

rtos_result_t rtos_task_create_static(rtos_task_func_t func, const char *name,
                                      rtos_stack_size_t stack_size,
                                      void *params, rtos_priority_t priority,
                                      rtos_stack_t *stack_buf,
                                      rtos_tcb_t *tcb_buf,
                                      rtos_task_handle_t *handle);

void rtos_task_delete(rtos_task_handle_t handle);

void rtos_task_delay(uint32_t delay_ms);

void rtos_schedule_start(void);

/****************************************************
 * Mutex API
 ****************************************************/

rtos_mutex_t rtos_mutex_create(void);

rtos_mutex_t rtos_mutex_create_static(rtos_static_mutex_buf_t *buffer);

rtos_result_t rtos_mutex_take(rtos_mutex_t mutex);

rtos_result_t rtos_mutex_give(rtos_mutex_t mutex);

void rtos_mutex_delete(rtos_mutex_t mutex);

/****************************************************
 * Event Flag API
 ****************************************************/
// 動的EventFlag生成
rtos_flag_t rtos_flag_create(void);

// 静的EventFlag生成
rtos_flag_t rtos_flag_create_static(rtos_static_flag_buf_t *buffer);

// EventFlag Set
rtos_bit_t rtos_flag_set(rtos_flag_t flag, rtos_bit_t setBit);

// EventFlag wait
rtos_bit_t rtos_flag_wait(rtos_flag_t flag, rtos_bit_t waitBit,
                          rtos_base_t clearOnExit, rtos_base_t waitAllBits,
                          rtos_time_ms_t timeout_ms);

/****************************************************
 * Queue API
 ****************************************************/
rtos_queue_t rtos_queue_create(rtos_queue_size_t itemSize,
                               rtos_queue_size_t queueLength);

rtos_queue_t rtos_queue_create_static(rtos_queue_size_t itemSize,
                                      rtos_queue_size_t queueLength,
                                      uint8_t *queueStorage,
                                      rtos_static_queue_buf_t *buffer);

rtos_result_t rtos_queue_send(rtos_queue_t queue, const void *item,
                              rtos_time_ms_t timeout_ms);

rtos_result_t rtos_queue_receive(rtos_queue_t queue, void *item,
                                 rtos_time_ms_t timeout_ms);

#endif
