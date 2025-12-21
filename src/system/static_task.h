#ifndef STATIC_TASK_H
#define STATIC_TASK_H

#include "rtos_wrapper.h"
#include "typedef.h"

extern int8_t taskInit(void);
extern rtos_task_func_t usbFlush_task(void *params);
extern rtos_task_func_t usbDrain_task(void *params);

#endif // STATIC_TASK_H
