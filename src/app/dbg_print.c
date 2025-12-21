#include "dbg_print.h"

#include <stdarg.h>

#include "pico/time.h"
#include "rtos_wrapper.h"
#include "typedef.h"
#include "usb_comm.h"

/****************************************************
 * forward declaration
 ****************************************************/
bool init_dbgPrint(void);
int32_t dbgPrint(dbg_level_t level, const char *format, ...);

#define DBG_PRINT_BUFFER_SIZE 1024
uint8_t s_buffer[DBG_PRINT_BUFFER_SIZE];
const char *dbg_level_strings[4] = {"DEBUG", "INFO ", "WARN ", "ERROR"};

// テキスト色
#define ANSI_COLOR_BLACK "\033[30m"
#define ANSI_COLOR_RED "\033[31m"
#define ANSI_COLOR_YELLOW "\033[33m"
#define ANSI_COLOR_BLUE "\033[34m"
#define ANSI_COLOR_CYAN "\033[36m"
#define ANSI_COLOR_WHITE "\033[37m"
#define ANSI_COLOR_RESET "\033[0m"

const char *dbg_level_colors[4] = {
    ANSI_COLOR_CYAN,   // DEBUG
    ANSI_COLOR_WHITE,  // INFO
    ANSI_COLOR_YELLOW, // WARN
    ANSI_COLOR_RED     // ERROR
};

// dbg bufferのmutex資源
rtos_mutex_t s_mtxDbgPrint = NULL;

bool init_dbgPrint(void)
{
    s_mtxDbgPrint = rtos_mutex_create();
    if (s_mtxDbgPrint == NULL)
    {
        // TODO: Assert
        return false;
    }
    return true;
}

int32_t dbgPrint(dbg_level_t level, const char *format, ...)
{
    rtos_mutex_take(s_mtxDbgPrint);
    int32_t ret = E_OTHER;

    memset(s_buffer, 0, DBG_PRINT_BUFFER_SIZE);

    // [LEVEL][{clock}] のプレフィックスを追加
    // levelに合わせて色付けも行う
    uint32_t clock = to_ms_since_boot(get_absolute_time());
    int32_t prefix_len =
        snprintf((char *)s_buffer, DBG_PRINT_BUFFER_SIZE, "%s[%s][%06u] ",
                 dbg_level_colors[level], dbg_level_strings[level], clock);

    if (prefix_len < 0 || prefix_len >= DBG_PRINT_BUFFER_SIZE)
    {
        ret = E_BUFSIZE; // バッファ不足
        goto exit;
    }

    // 残りのバッファにユーザーメッセージを追加
    va_list args;
    va_start(args, format);
    int32_t msg_len =
        vsnprintf((char *)s_buffer + prefix_len,
                  DBG_PRINT_BUFFER_SIZE - prefix_len, format, args);
    va_end(args);
    if (msg_len < 0)
    {
        ret = E_OTHER;
        goto exit;
    }

    // 色をリセットする
    int32_t suffix_len = snprintf((char *)s_buffer + prefix_len + msg_len,
                                  DBG_PRINT_BUFFER_SIZE - prefix_len - msg_len,
                                  "%s", ANSI_COLOR_RESET);
    if (suffix_len < 0)
    {
        ret = E_OTHER;
        goto exit;
    }

    // 実際に書き込まれた総長さを計算
    int32_t total_len = prefix_len + msg_len + suffix_len;
    if (total_len >= DBG_PRINT_BUFFER_SIZE)
    {
        // 切り詰められた場合、実際のバッファサイズ-1（null終端分）
        total_len = DBG_PRINT_BUFFER_SIZE - 1;
    }

    // USB経由で送信
    int32_t sent_len = usbTx((const char *)s_buffer, total_len);
    if (sent_len < 0)
    {
        ret = sent_len; // 送り切れる or 負のエラーが返る
        goto exit;
    }
    ret = E_SUCCESS;

exit:
    rtos_mutex_give(s_mtxDbgPrint);
    return ret;
}
