#include <vowframework/private/log.h>
#include <vowframework/private/timer.h>

#include <vowframework/handle.h>
#include <vowframework/log.h>
#include <vowframework/memory.h>
#include <vowframework/timer.h>

#include <stdbool.h>

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

static VowTimerData vow_timer_data = { 0 };

static void complete_duration(VowHandle handle)
{
    vow_timer_data.timers[handle].callback(handle);
    if (vow_timer_data.timers[handle].repeat)
    {
        vow_timer_data.timers[handle].totalTime = 0.0f;
    }
    else
    {
        vow_timer_destroy(handle);
    }
}

void vow_timer_initialize(void)
{
    vow_timer_data.timers = vow_memory_allocate(VOW_TIMER_CAPACITY * sizeof(VowTimer));
    vow_timer_data.count = 1;
}

void vow_timer_finalize(void)
{
    vow_memory_free(vow_timer_data.timers);
    vow_timer_data = (VowTimerData) { 0 };
}

void vow_timer_update(float frameTime)
{
    for (VowHandle i = 1; i < VOW_TIMER_CAPACITY; i++)
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

VowHandle vow_timer_create(float duration, bool repeat, VowTimerCallback callback)
{
    const VowHandle handle = ++vow_timer_data.count;
    if (handle == VOW_HANDLE_INVALID)
    {
        vow_log_print(VOW_LOG_LEVEL_WARNING, "Failed to create timer.");
        return VOW_HANDLE_INVALID;
    }
    vow_timer_data.timers[handle].handle = handle;
    vow_timer_data.timers[handle].active = true;
    vow_timer_data.timers[handle].duration = duration;
    vow_timer_data.timers[handle].repeat = repeat;
    vow_timer_data.timers[handle].callback = callback;
    return handle;
}

void vow_timer_destroy(VowHandle handle)
{
    vow_timer_data.timers[handle] = (VowTimer) { 0 };
    vow_timer_data.count--;
}

void vow_timer_toggle(VowHandle handle, bool flag)
{
    vow_timer_data.timers[handle].active = flag;
}

void vow_timer_elapsed(VowHandle handle, float elapsed)
{
    if (elapsed >= vow_timer_data.timers[handle].duration)
    {
        complete_duration(handle);
    }
    vow_timer_data.timers[handle].totalTime = elapsed;
}

bool vow_timer_is_active(VowHandle handle)
{
    return vow_timer_data.timers[handle].active;
}

float vow_timer_get_elapsed(VowHandle handle)
{
    return vow_timer_data.timers[handle].totalTime;
}

float vow_timer_get_progress(VowHandle handle)
{
    const float progress = vow_timer_data.timers[handle].totalTime / vow_timer_data.timers[handle].duration;
    return progress;
}