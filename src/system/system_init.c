#include "system_init.h"
#include "dbg_print.h"
#include "static_task.h"
#include "typedef.h"
#include "usb_comm.h"

bool systemInit()
{
    // stdioの初期化
    if (!stdio_init_all())
    {
        return false;
    }

    // Wi-Fiチップの初期化
    if (cyw43_arch_init())
    {
        return false;
    }

    if (!taskInit())
    {
        return false;
    }

    // USB通信の初期化
    // USB通信に用いるリングバッファの初期化も含む
    if (!usbCommInit())
    {
        return false;
    }

    if (!init_dbgPrint())
    {
        return false;
    }

    return true;
}
