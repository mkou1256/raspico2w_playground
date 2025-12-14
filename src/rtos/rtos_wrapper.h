#ifndef RTOS_WRAPPER_H
#define RTOS_WRAPPER_H

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <stdint.h>

/****************************************************
 * Type Definitions
 ****************************************************/

// base type
typedef int32_t rtos_base_t;
typedef uint32_t rtos_ubase_t;
typedef enum {
    RTOS_OK = 0,
    RTOS_ERROR = -1,
    RTOS_TIMEOUT = -2
} rtos_result_t;

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
typedef StaticSemaphore_t rtos_static_queue_t;

/******************************************************************************
 * Priority Constants
 ******************************************************************************/

#define RTOS_PRIORITY_IDLE    0
#define RTOS_PRIORITY_LOW     1
#define RTOS_PRIORITY_NORMAL  2
#define RTOS_PRIORITY_HIGH    3

/****************************************************
 * Task API
 ****************************************************/

rtos_result_t rtos_task_create(
        rtos_task_func_t func,
        const char *name,
        rtos_stack_size_t stack_size,
        void *params,
        rtos_priority_t priority,
        rtos_task_handle_t *handle
        );

rtos_result_t rtos_task_create_static(
        rtos_task_func_t func,
        const char *name,
        rtos_stack_size_t stack_size,
        void *params,
        rtos_priority_t priority,
        rtos_stack_t *stack_buf,
        rtos_tcb_t *tcb_buf,
        rtos_task_handle_t *handle
        );

void rtos_task_delete(rtos_task_handle_t handle);
    
void rtos_task_delay(uint32_t delay_ms);

void rtos_schedule_start(void);

/****************************************************
 * Mutex API
 ****************************************************/

rtos_mutex_t rtos_mutex_create(void);

rtos_mutex_t rtos_mutex_create_static(rtos_static_queue_t *buffer);

rtos_result_t rtos_mutex_take(rtos_mutex_t mutex);

rtos_result_t rtos_mutex_give(rtos_mutex_t mutex);

void rtos_mutex_delete(rtos_mutex_t mutex);

#endif
