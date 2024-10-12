////////////////////////////////////////////////////////////////////////////////
// Dependencies
////////////////////////////////////////////////////////////////////////////////

#include <vowengine/private/log.h>

#include <vowengine/log.h>
#include <vowengine/tuple.h>
#include <vowengine/window.h>

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>

#include <assert.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////////
// Types
////////////////////////////////////////////////////////////////////////////////

typedef struct VowWindowData
{
    GLFWwindow* handle;
    void (*close_callback)(void);
    void (*position_callback)(int x, int y);
    void (*size_callback)(int width, int height);
}
VowWindowData;

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

static VowWindowData vow_window_data = { 0 };

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

static void close_callback(GLFWwindow* window)
{
    if (vow_window_data.close_callback)
    {
        glfwSetWindowShouldClose(vow_window_data.handle, GL_FALSE);
        vow_window_data.close_callback();
    }
}

static void position_callback(GLFWwindow* window, int x, int y)
{
    if (vow_window_data.position_callback)
    {
        vow_window_data.position_callback(x, y);
    }
}

static void size_callback(GLFWwindow* window, int width, int height)
{
    if (vow_window_data.size_callback)
    {
        vow_window_data.size_callback(width, height);
    }
}

////////////////////////////////////////////////////////////////////////////////
// Functions <vowengine/window.h>
////////////////////////////////////////////////////////////////////////////////

void vow_window_create(int width, int height, const char* title)
{
    assert(!vow_window_data.handle);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    vow_window_data.handle = glfwCreateWindow(width, height, title, (void*) 0, (void*) 0);
    if (!vow_window_data.handle)
    {
        vow_log_print(VOW_LOG_LEVEL_FATAL, "Failed to create window.");
        vow_window_destroy();
        exit(0);
    }
    const int context_version_major = glfwGetWindowAttrib(vow_window_data.handle, GLFW_CONTEXT_VERSION_MAJOR);
    const int context_version_minor = glfwGetWindowAttrib(vow_window_data.handle, GLFW_CONTEXT_VERSION_MINOR);
    if (context_version_major != 4 || context_version_minor != 6)
    {
        vow_log_print(VOW_LOG_LEVEL_FATAL, "Failed to create a valid OpenGL 4.6 context.");
        vow_window_destroy();
        exit(0);
    }
    glfwMakeContextCurrent(vow_window_data.handle);
    (void) gladLoadGL(glfwGetProcAddress);
    glfwSetWindowCloseCallback(vow_window_data.handle, close_callback);
    glfwSetWindowPosCallback(vow_window_data.handle, position_callback);
    glfwSetWindowSizeCallback(vow_window_data.handle, size_callback);
    vow_window_vsync(1);
}

void vow_window_destroy(void)
{
    glfwDestroyWindow(vow_window_data.handle);
    vow_window_data = (VowWindowData) { 0 };
}

void vow_window_close(void)
{
    glfwSetWindowShouldClose(vow_window_data.handle, GLFW_TRUE);
}

void vow_window_close_callback(void (*callback)(void))
{
    vow_window_data.close_callback = callback;
}

void vow_window_position(int x, int y)
{
    glfwSetWindowPos(vow_window_data.handle, x, y);
}

void vow_window_position_callback(void (*callback)(int x, int y))
{
    vow_window_data.position_callback = callback;
}

void vow_window_size(int width, int height)
{
    glfwSetWindowSize(vow_window_data.handle, width, height);
}

void vow_window_size_callback(void (*callback)(int width, int height))
{
    vow_window_data.size_callback = callback;
}

void vow_window_title(const char* title)
{
    glfwSetWindowTitle(vow_window_data.handle, title);
}

void vow_window_vsync(bool flag)
{
    glfwSwapInterval(flag);
}

bool vow_window_should_close(void)
{
    return glfwWindowShouldClose(vow_window_data.handle);
}

VowTuple2i vow_window_get_position(void)
{
    VowTuple2i position;
    glfwGetWindowPos(vow_window_data.handle, &position.x, &position.y);
    return position;
}

VowTuple2i vow_window_get_content_size(void)
{
    VowTuple2i content_size;
    glfwGetWindowSize(vow_window_data.handle, &content_size.x, &content_size.y);
    return content_size;
}

VowTuple2i vow_window_get_frame_size(void)
{
    const VowTuple2i content_size = vow_window_get_content_size();
    int left, top, right, bottom;
    glfwGetWindowFrameSize(vow_window_data.handle, &left, &right, &top, &bottom);
    const VowTuple2i frame_size =
    {
        content_size.x + left + right,
        content_size.y + top + bottom
    };
    return frame_size;
}