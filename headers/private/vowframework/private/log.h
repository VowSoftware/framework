#ifndef VOW_GUARD_LOG_PRIVATE
#define VOW_GUARD_LOG_PRIVATE

#include <vowframework/log.h>

#ifdef NDEBUG
    vow_log_print(level, format, ...) ((void) 0)
#else
    void vow_log_print(VowLogLevel level, const char* format, ...);
#endif

#endif