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
    double totalTime;
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

void vow_timer_update(double frameTime)
{
    for (int i = 1; i < VOW_TIMER_CAPACITY; i++)
    {
        if (vow_timer_data.timers[i].handle)
        {
            if (vow_timer_data.timers[i].active)
            {
                vow_timer_data.timers[i].totalTime += frameTime;
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// Functions <vowengine/timer.h>
////////////////////////////////////////////////////////////////////////////////

VowHandle vow_timer_create(void)
{
    const int index = ++vow_timer_data.count;
    VowHandle handle = vow_handle_create(index, VOW_HANDLE_TYPE_TIMER);
    if (handle == VOW_HANDLE_INVALID)
    {
        vow_log_print(VOW_LOG_LEVEL_WARNING, "Failed to create timer.");
        return VOW_HANDLE_INVALID;
    }
    vow_timer_data.timers[index].active = true;
    return handle;
}

void vow_timer_destroy(VowHandle handle)
{
    const int index = vow_handle_resolve(handle, VOW_HANDLE_TYPE_TIMER);
    vow_timer_data.timers[index] = (VowTimer) { 0 };
    vow_timer_data.count = 0;
}

void vow_timer_toggle(VowHandle handle, bool flag)
{
    const int index = vow_handle_resolve(handle, VOW_HANDLE_TYPE_TIMER);
    vow_timer_data.timers[index].active = flag;
}

void vow_timer_reset(VowHandle handle)
{
    const int index = vow_handle_resolve(handle, VOW_HANDLE_TYPE_TIMER);
    vow_timer_data.timers[index].totalTime = 0.0;
}

bool vow_timer_is_active(VowHandle handle)
{
    const int index = vow_handle_resolve(handle, VOW_HANDLE_TYPE_TIMER);
    return vow_timer_data.timers[index].active;
}

double vow_timer_get_elapsed(VowHandle handle)
{
    const int index = vow_handle_resolve(handle, VOW_HANDLE_TYPE_TIMER);
    return vow_timer_data.timers[index].totalTime;
}