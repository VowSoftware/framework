////////////////////////////////////////////////////////////////////////////////
// Dependencies
////////////////////////////////////////////////////////////////////////////////

#include <vowengine/private/handle.h>
#include <vowengine/private/log.h>
#include <vowengine/private/timer.h>

#include <vowengine/handle.h>
#include <vowengine/log.h>
#include <vowengine/memory.h>
#include <vowengine/timer.h>

#include <stdbool.h>

////////////////////////////////////////////////////////////////////////////////
// Types
////////////////////////////////////////////////////////////////////////////////

typedef struct VowTimer
{
    VowHandle handle;
    bool active;
    float duration;
    bool repeat;
    VowTimerCallback callback;
    float totalTime;
}
VowTimer;

typedef struct VowTimerData
{
    VowTimer* timers;
    int count;
}
VowTimerData;

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

static VowTimerData vow_timer_data = { 0 };

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

static void complete_duration(VowHandleIndex index)
{
    const VowHandle handle = vow_timer_data.timers[index].handle;
    vow_timer_data.timers[index].callback(handle);
    if (vow_timer_data.timers[index].repeat)
    {
        vow_timer_data.timers[index].totalTime = 0.0f;
    }
    else
    {
        vow_timer_destroy(handle);
    }
}

////////////////////////////////////////////////////////////////////////////////
// Functions <vowengine/private/timer.h>
////////////////////////////////////////////////////////////////////////////////

void vow_timer_initialize(void)
{
    vow_timer_data.timers = vow_memory_allocate(VOW_TIMER_CAPACITY * sizeof(VowTimer));
}

void vow_timer_finalize(void)
{
    vow_memory_free(vow_timer_data.timers);
    vow_timer_data = (VowTimerData) { 0 };
}

void vow_timer_update(float frameTime)
{
    for (int i = VOW_HANDLE_MIN_INDEX; i < VOW_TIMER_CAPACITY; i++)
    {
        if (vow_timer_data.timers[i].handle && vow_timer_data.timers[i].active)
        {
            vow_timer_data.timers[i].totalTime += frameTime;
            if (vow_timer_data.timers[i].totalTime > vow_timer_data.timers[i].duration)
            {
                complete_duration(i);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// Functions <vowengine/timer.h>
////////////////////////////////////////////////////////////////////////////////

VowHandle vow_timer_create(float duration, bool repeat, VowTimerCallback callback)
{
    const VowHandleIndex index = ++vow_timer_data.count;
    const VowHandle handle = vow_handle_create(index, VOW_HANDLE_TYPE_TIMER);
    if (handle == VOW_HANDLE_INVALID)
    {
        vow_log_print(VOW_LOG_LEVEL_WARNING, "Failed to create timer.");
        return VOW_HANDLE_INVALID;
    }
    vow_timer_data.timers[index].handle = handle;
    vow_timer_data.timers[index].active = true;
    vow_timer_data.timers[index].duration = duration;
    vow_timer_data.timers[index].repeat = repeat;
    vow_timer_data.timers[index].callback = callback;
    return handle;
}

void vow_timer_destroy(VowHandle handle)
{
    const VowHandleIndex index = vow_handle_resolve(handle, VOW_HANDLE_TYPE_TIMER);
    vow_timer_data.timers[index] = (VowTimer) { 0 };
    vow_timer_data.count--;
}

void vow_timer_toggle(VowHandle handle, bool flag)
{
    const VowHandleIndex index = vow_handle_resolve(handle, VOW_HANDLE_TYPE_TIMER);
    vow_timer_data.timers[index].active = flag;
}

void vow_timer_elapsed(VowHandle handle, float elapsed)
{
    const VowHandleIndex index = vow_handle_resolve(handle, VOW_HANDLE_TYPE_TIMER);
    if (elapsed >= vow_timer_data.timers[index].duration)
    {
        complete_duration(index);
    }
    vow_timer_data.timers[index].totalTime = elapsed;
}

bool vow_timer_is_active(VowHandle handle)
{
    const VowHandleIndex index = vow_handle_resolve(handle, VOW_HANDLE_TYPE_TIMER);
    return vow_timer_data.timers[index].active;
}

float vow_timer_get_elapsed(VowHandle handle)
{
    const VowHandleIndex index = vow_handle_resolve(handle, VOW_HANDLE_TYPE_TIMER);
    return vow_timer_data.timers[index].totalTime;
}

float vow_timer_get_progress(VowHandle handle)
{
    const VowHandleIndex index = vow_handle_resolve(handle, VOW_HANDLE_TYPE_TIMER);
    const float progress = vow_timer_data.timers[index].totalTime / vow_timer_data.timers[index].duration;
    return progress;
}