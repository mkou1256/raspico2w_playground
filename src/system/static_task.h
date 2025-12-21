#ifndef STATIC_TASK_H
#define STATIC_TASK_H

#include "rtos_wrapper.h"
#include "typedef.h"

extern bool taskInit(void);
extern void usbFlush_task(void *params);
extern void usbDrain_task(void *params);

#endif // STATIC_TASK_H
