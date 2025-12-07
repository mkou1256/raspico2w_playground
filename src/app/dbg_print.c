#include "dbg_print.h"
#include "typedef.h"
#include "usb_comm.h"
#include "pico/stdlib.h"
#include "pico/time.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define DBG_PRINT_BUFFER_SIZE  256
uint8_t s_buffer[DBG_PRINT_BUFFER_SIZE];
const char* dbg_level_strings[4] = {
    "DEBUG",
    "INFO ",
    "WARN ",
    "ERROR"
};

// テキスト色
#define ANSI_COLOR_BLACK   "\033[30m"
#define ANSI_COLOR_RED     "\033[31m"
#define ANSI_COLOR_YELLOW  "\033[33m"
#define ANSI_COLOR_BLUE    "\033[34m"
#define ANSI_COLOR_CYAN    "\033[36m"
#define ANSI_COLOR_WHITE   "\033[37m"
#define ANSI_COLOR_RESET   "\033[0m"

const char* dbg_level_colors[4] = {
    ANSI_COLOR_WHITE,   // DEBUG
    ANSI_COLOR_CYAN,    // INFO
    ANSI_COLOR_YELLOW,  // WARN
    ANSI_COLOR_RED      // ERROR
};

int32_t dbgPrint(dbg_level_t level, const char* format, ...)
{
    memset(s_buffer, 0, DBG_PRINT_BUFFER_SIZE);
    
    // [LEVEL][{clock}] のプレフィックスを追加
    // levelに合わせて色付けも行う
    uint32_t clock = to_ms_since_boot(get_absolute_time());
    int32_t prefix_len = snprintf((char*)s_buffer, DBG_PRINT_BUFFER_SIZE, 
                                   "%s[%s][%06u] ", dbg_level_colors[level], dbg_level_strings[level], clock);
    
    if (prefix_len < 0 || prefix_len >= DBG_PRINT_BUFFER_SIZE) {
        return -1; // バッファ不足
    }

    // 残りのバッファにユーザーメッセージを追加
    va_list args;
    va_start(args, format);
    int32_t msg_len = vsnprintf((char*)s_buffer + prefix_len, 
                                DBG_PRINT_BUFFER_SIZE - prefix_len, 
                                format, args);
    va_end(args);
    if (msg_len < 0) {
        return -1; // エラー
    }

    // 色をリセットする
    int32_t reset_len = snprintf((char*)s_buffer + prefix_len + msg_len, 
                                 DBG_PRINT_BUFFER_SIZE - prefix_len - msg_len, 
                                 "%s", ANSI_COLOR_RESET);
    if (reset_len < 0) {
        return -1; // エラー
    }
    
    // 実際に書き込まれた総長さを計算
    int32_t total_len = prefix_len + msg_len;
    if (total_len >= DBG_PRINT_BUFFER_SIZE) {
        // 切り詰められた場合、実際のバッファサイズ-1（null終端分）
        total_len = DBG_PRINT_BUFFER_SIZE - 1;
    }
    
    // USB経由で送信
    int32_t sent_len = usbTx((const char*)s_buffer, total_len);
    if (sent_len < 0) {
        return sent_len; // エラー
    }
    return E_SUCCESS;
}