#ifndef __DBG_PRINT__
#define __DBG_PRINT__

#include "pico/stdlib.h"

typedef enum {
    DBG_LEVEL_DEBUG = 0,
    DBG_LEVEL_INFO,
    DBG_LEVEL_WARN,
    DBG_LEVEL_ERROR
} dbg_level_t;

extern int32_t dbgPrint(dbg_level_t level, const char* format, ...);

#endif // __DBG_PRINT__