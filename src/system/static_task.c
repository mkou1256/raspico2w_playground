#include "static_task.h"
#include "rtos_wrapper.h"
#include "typedef.h"
#include "usb_comm.h"

/****************************************************
 * forward declaration
 ****************************************************/
bool taskInit();

// usb comm task
#define STACKSIZE_USB_FLUSH 512
rtos_stack_t stack_usbFlush[STACKSIZE_USB_FLUSH];
rtos_tcb_t tcb_usbFlush;
rtos_task_handle_t task_handle_usbFlush;

#define STACKSIZE_USB_DRAIN 512
rtos_stack_t stack_usbDrain[STACKSIZE_USB_DRAIN];
rtos_tcb_t tcb_usbDrain;
rtos_task_handle_t task_handle_usbDrain;

bool taskInit()
{
    rtos_result_t ret =
        rtos_task_create_static(usbFlush_task, "usbFlush", STACKSIZE_USB_FLUSH,
                                NULL, RTOS_PRIORITY_NORMAL, stack_usbFlush,
                                &tcb_usbFlush, &task_handle_usbFlush);

    ret +=
        rtos_task_create_static(usbDrain_task, "usbDrain", STACKSIZE_USB_DRAIN,
                                NULL, RTOS_PRIORITY_NORMAL, stack_usbDrain,
                                &tcb_usbDrain, &task_handle_usbDrain);

    return (ret == RTOS_OK) ? true : false;
}