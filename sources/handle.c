////////////////////////////////////////////////////////////////////////////////
// Dependencies
////////////////////////////////////////////////////////////////////////////////

#include <vowengine/private/handle.h>
#include <vowengine/private/log.h>

#include <vowengine/handle.h>
#include <vowengine/log.h>

#include <assert.h>

////////////////////////////////////////////////////////////////////////////////
// Functions <vowengine/private/handle.h>
////////////////////////////////////////////////////////////////////////////////

VowHandle vow_handle_create(int index, VowHandleType type)
{
    assert(index > 0);
    switch (type)
    {
        case VOW_HANDLE_TYPE_TIMER:
            if (index > VOW_TIMER_CAPACITY)
            {
                vow_log_print(VOW_LOG_LEVEL_WARNING, "Failed to create handle. Timer capacity reached.");
                return VOW_HANDLE_INVALID;
            }
    }
    const VowHandle handle = index << 2 | type;
    return handle;
}

int vow_handle_resolve(VowHandle handle, VowHandleType type)
{
    const VowHandleType actual_type = handle & 0xff;
    assert(actual_type == type);
    const int index = handle & 0xffffffff00;
    return index;
}