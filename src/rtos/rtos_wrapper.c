#include "rtos_wrapper.h"
#include "FreeRTOS.h"
#include "portmacrocommon.h"
#include "projdefs.h"

/****************************************************
 * Task Implementation
 ****************************************************/

rtos_result_t rtos_task_create(
        rtos_task_func_t func,
        const char *name,
        rtos_stack_size_t stack_size,
        void *params,
        rtos_priority_t priority,
        rtos_task_handle_t *handle
        )
{
    if (func == NULL) {
        return RTOS_ERROR;
    }

    BaseType_t res = xTaskCreate(
            func,
            name,
            stack_size,
            params,
            priority,
            handle
            );
    return (res == pdPASS) ? RTOS_OK : RTOS_ERROR;
}

rtos_result_t rtos_task_create_static(
        rtos_task_func_t func,
        const char *name,
        rtos_stack_size_t stack_size,
        void *params,
        rtos_priority_t priority,
        rtos_stack_t *stack_buf,
        rtos_tcb_t *tcb_buf,
        rtos_task_handle_t *handle
        )
{
    if (func == NULL ||
            stack_buf == NULL ||
            tcb_buf == NULL ||
            handle == NULL
            ) {
        return RTOS_ERROR;
    }

    *handle = xTaskCreateStatic(
           func, 
           name, 
           stack_size, 
           params,
           priority, 
           stack_buf, 
           tcb_buf);

    return (*handle != NULL) ? RTOS_OK : RTOS_ERROR;
}

void rtos_task_delete(rtos_task_handle_t handle)
{
    vTaskDelete(handle);
}

void rtos_task_delay(uint32_t delay_ms)
{
    vTaskDelay(pdMS_TO_TICKS(delay_ms));
}


/****************************************************
 * Mutex Implementation
 ****************************************************/

rtos_mutex_t rtos_mutex_create(void)
{
    return xSemaphoreCreateMutex();
}

rtos_mutex_t rtos_mutex_create_static(rtos_static_queue_t *buffer)
{
    if (buffer == NULL) {
        return NULL;
    }

    return xSemaphoreCreateMutexStatic(buffer);
}

rtos_result_t rtos_mutex_take(rtos_mutex_t mutex)
{
    if (mutex == NULL) {
        return RTOS_ERROR;
    }

    BaseType_t res = xSemaphoreTake(mutex, portMAX_DELAY);
    return (res == pdTRUE) ? RTOS_OK : RTOS_ERROR;
}

rtos_result_t rtos_mutex_give(rtos_mutex_t mutex)
{
    if (mutex == NULL) {
        return RTOS_ERROR;
    }

    BaseType_t res = xSemaphoreGive(mutex);
    return (res  == pdTRUE) ? RTOS_OK : RTOS_ERROR;
}

void rtos_mutex_delete(rtos_mutex_t mutex)
{
    if (mutex != NULL) {
        vSemaphoreDelete(mutex);
    }
}

