#include "system_init.h"
#include "dbg_print.h"
#include "typedef.h"
#include "usb_comm.h"

int8_t systemInit()
{
    // stdioの初期化
    if (!stdio_init_all())
    {
        return E_INIT;
    }

    // Wi-Fiチップの初期化
    if (cyw43_arch_init())
    {
        return E_INIT;
    }

    if (taskInit() != E_SUCCESS)
    {
        return E_INIT;
    }

    // USB通信の初期化
    // USB通信に用いるリングバッファの初期化も含む
    if (usbCommInit() != E_SUCCESS)
    {
        return E_INIT;
    }

    if (init_dbgPrint() != E_SUCCESS)
    {
        return E_INIT;
    }

    return E_SUCCESS;
}
