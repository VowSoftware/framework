#include <vowframework/private/timer.h>

#include <vowframework/framework.h>

#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>

#include <assert.h>

typedef struct VowFrameworkData
{
    float lastTime;
}
VowFrameworkData;

static VowFrameworkData vow_framework_data = { 0 };

static void glfw_error_callback(int error_code, const char* description)
{
    vow_log_print(VOW_LOG_LEVEL_ERROR, "GLFW: %d %s", error_code, description);
}

////////////////////////////////////////////////////////////////////////////////
// Functions <vowframework/framework.h>
////////////////////////////////////////////////////////////////////////////////

void vow_framework_initialize(void)
{
    glfwSetErrorCallback(glfw_error_callback);
    assert(glfwInit());
    vow_timer_initialize();
}

void vow_framework_finalize(void)
{
    vow_timer_finalize();
    glfwTerminate();
    vow_framework_data = (VowFrameworkData) { 0 };
}

void vow_framework_update(void)
{
    const float totalTime = (float) glfwGetTime();
    const float frameTime = totalTime - vow_framework_data.lastTime;
    vow_timer_update(frameTime);
    vow_framework_data.lastTime = totalTime;
}