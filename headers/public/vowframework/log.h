#ifndef VOW_GUARD_LOG
#define VOW_GUARD_LOG

////////////////////////////////////////////////////////////////////////////////
// Severity levels for log messages.
//
// * `VOW_LOG_LEVEL_INFO`: Don't require the user's attention.
//                         These are often useful for debugging purposes.
// * `VOW_LOG_LEVEL_WARNING`: Something behaved in a potentially unexpected or undesirable way.
// * `VOW_LOG_LEVEL_ERROR`: Something failed that the user needs to know about,
//                          but program execution is able to continue.
// * `VOW_LOG_LEVEL_FATAL`: Something critical failed and the program must be terminated.
////////////////////////////////////////////////////////////////////////////////
typedef enum VowLogLevel
{
    VOW_LOG_LEVEL_INFO,
    VOW_LOG_LEVEL_WARNING,
    VOW_LOG_LEVEL_ERROR,
    VOW_LOG_LEVEL_FATAL
}
VowLogLevel;

////////////////////////////////////////////////////////////////////////////////
// Filters log messages by a minimum severity level.
//
// Parameters
//   * `level`: Severity level.
////////////////////////////////////////////////////////////////////////////////
void vow_log_level(VowLogLevel level);

#endif