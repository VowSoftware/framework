////////////////////////////////////////////////////////////////////////////////
// Dependencies
////////////////////////////////////////////////////////////////////////////////

#include <vowengine/engine.h>

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
    vow_engine_initialize();
    vow_window_create(960, 540, "Vow Engine Example: Window");
    VowHandle handle = vow_timer_create();
    while (!vow_window_should_close())
    {
        vow_engine_update();
        float time = vow_timer_get_elapsed(handle);
        if (time > 3.0f)
        {
            break;
        }
    }
    vow_window_destroy();
    vow_engine_finalize();
    return 0;
}