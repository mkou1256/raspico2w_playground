#include "rtos_wrapper.h"
#include "typedef.h"
#include "usb_comm.h"

// usb comm task
#define STACKSIZE_USB_FLUSH 512
rtos_stack_t stack_usbFlush[STACKSIZE_USB_FLUSH];
rtos_tcb_t tcb_usbFlush;
rtos_task_handle_t task_handle_usbFlush;

#define STACKSIZE_USB_DRAIN 512
rtos_stack_t stack_usbDrain[STACKSIZE_USB_DRAIN];
rtos_tcb_t tcb_usbDrain;
rtos_task_handle_t task_handle_usbDrain;

int8_t taskInit()
{
    int8_t ret = E_SUCCESS;

    ret |= rtos_task_create_static(usbFlush_task, "usbFlush", STACKSIZE_USB_FLUSH, NULL, RTOS_PRIORITY_NORMAL,
                                   stack_usbFlush, &tcb_usbFlush, &task_handle_usbFlush);

    ret |= rtos_task_create_static(usbDrain_task, "usbDrain", STACKSIZE_USB_DRAIN, NULL, RTOS_PRIORITY_NORMAL,
                                   stack_usbDrain, &tcb_usbDrain, &task_handle_usbDrain);

    return (ret == E_SUCCESS) ? E_SUCCESS : E_INIT;
}
