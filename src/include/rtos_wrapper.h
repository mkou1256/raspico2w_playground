#ifndef __RTOS_WRAPPER__
#define __RTOS_WRAPPER__

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

// typedef wrapper
#define TRUE pdTRUE
#define FALSE pdFALSE
#define mtx_handle_t  SemaphoreHandle_t

// function wrapper
#define make_mtx() xSemaphoreCreateMutex()
#define take_mtx(mtx_handle) \
    xSemaphoreTake(mtx_handle, portMAX_DELAY)
#define give_mtx(mtx_handle) \
    xSemaphoreGive(mtx_handle)

#endif
