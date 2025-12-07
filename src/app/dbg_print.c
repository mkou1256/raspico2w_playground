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

int32_t dbgPrint(const char* format, ...)
{
    memset(s_buffer, 0, DBG_PRINT_BUFFER_SIZE);
    
    // [DBG][{clock}] のプレフィックスを追加
    uint32_t clock = to_ms_since_boot(get_absolute_time());
    int32_t prefix_len = snprintf((char*)s_buffer, DBG_PRINT_BUFFER_SIZE, 
                                   "[DBG][%06u] ", clock);
    
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
    
    // 実際に書き込まれた総長さを計算
    int32_t total_len = prefix_len + msg_len;
    if (total_len >= DBG_PRINT_BUFFER_SIZE) {
        // 切り詰められた場合、実際のバッファサイズ-1（null終端分）
        total_len = DBG_PRINT_BUFFER_SIZE - 1;
    }
    
    // USBバッファにデータを追加
    usbBufferTx((const char*)s_buffer, (size_t)total_len);
    // USBバッファの内容を送信
    usbFlashTxBuffer();
    
    return total_len;
}