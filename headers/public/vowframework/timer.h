#ifndef VOW_GUARD_TIMER
#define VOW_GUARD_TIMER

#include <vowframework/handle.h>

#include <stdbool.h>

////////////////////////////////////////////////////////////////////////////////
// Function pointer for timer callbacks.
////////////////////////////////////////////////////////////////////////////////
typedef void (*VowTimerCallback)(VowHandle handle);

////////////////////////////////////////////////////////////////////////////////
// Creates a timer.
//
// Parameters
//   * `duration`: Seconds until the timer completes.
//   * `repeat`: Determines if the timer should reset back to 0 upon reaching `duration`.
//   * `callback`: Callback that's triggered upon reaching `duration`.
//
// Fails
//   * Amount of timers created exceeds `VOW_TIMER_CAPACITY`.
//
// Returns
//   * [Success] Handle to the created timer.
//   * [Failure] `VOW_HANDLE_INVALID`
////////////////////////////////////////////////////////////////////////////////
VowHandle vow_timer_create(float duration, bool repeat, VowTimerCallback callback);

////////////////////////////////////////////////////////////////////////////////
// Destroys a timer.
//
// Parameters
//   * `handle`: The timer's handle.
////////////////////////////////////////////////////////////////////////////////
void vow_timer_destroy(VowHandle handle);

////////////////////////////////////////////////////////////////////////////////
// Toggles a timer.
//
// Parameters
//   * `handle`: The timer's handle.
//   * `flag`: Determines if the timer should start or stop.
////////////////////////////////////////////////////////////////////////////////
void vow_timer_toggle(VowHandle handle, bool flag);

////////////////////////////////////////////////////////////////////////////////
// Sets the amount of seconds that a timer has been running for.
//
// If `elapsed` exceeds the timer's duration,
// then it will immediately stop and its callback will be triggered.
//
// Parameters
//   * `handle`: The timer's handle.
//   * `elapsed`: Amount of seconds that the timer has been running for.
////////////////////////////////////////////////////////////////////////////////
void vow_timer_elapsed(VowHandle handle, float elapsed);

////////////////////////////////////////////////////////////////////////////////
// Checks if a timer is active.
//
// An "active" timer is defined as a timer that is running and hasn't yet reached its duration.
//
// Parameters
//   * `handle`: The timer's handle.
//
// Returns
//   * [Success] `bool`
////////////////////////////////////////////////////////////////////////////////
bool vow_timer_is_active(VowHandle handle);

////////////////////////////////////////////////////////////////////////////////
// Gets the amount of seconds that a timer has been running for.
//
// Parameters
//   * `handle`: The timer's handle.
//
// Returns
//   * [Success] Amount of seconds that the timer has been running for.
////////////////////////////////////////////////////////////////////////////////
float vow_timer_get_elapsed(VowHandle handle);

////////////////////////////////////////////////////////////////////////////////
// Gets the normalized amount of seconds that a timer has been running for.
//
// "Normalized" seconds are between [0.0f, 1.0f].
//
// Parameters
//   * `handle`: The timer's handle.
//
// Returns
//   * [Success] Normalized amount of seconds that a timer has been running for.
////////////////////////////////////////////////////////////////////////////////
float vow_timer_get_progress(VowHandle handle);

#endif