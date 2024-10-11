////////////////////////////////////////////////////////////////////////////////
// Dependencies
////////////////////////////////////////////////////////////////////////////////

#include <vowengine/xlog.h>

#include <vowengine/log.h>
#include <vowengine/tuple.h>
#include <vowengine/window.h>

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>

#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////////
// Types
////////////////////////////////////////////////////////////////////////////////

typedef struct VowWindow
{
    GLFWwindow* handle;
    void (*close_callback)(void);
    void (*position_callback)(int x, int y);
    void (*size_callback)(int width, int height);
}
VowWindow;

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

static VowWindow g_window = { 0 };

////////////////////////////////////////////////////////////////////////////////
// Private Functions
////////////////////////////////////////////////////////////////////////////////

static void glfw_error_callback(int error_code, const char* description)
{
    vow_log_print(VOW_LOG_LEVEL_ERROR, "GLFW: %d %s", error_code, description);
}

static void close_callback(GLFWwindow* window)
{
    (void) window;
    if (g_window.close_callback)
    {
        glfwSetWindowShouldClose(g_window.handle, GL_FALSE);
        g_window.close_callback();
    }
}

static void position_callback(GLFWwindow* window, int x, int y)
{
    (void) window;
    if (g_window.position_callback)
    {
        g_window.position_callback(x, y);
    }
}

static void size_callback(GLFWwindow* window, int width, int height)
{
    (void) window;
    if (g_window.size_callback)
    {
        g_window.size_callback(width, height);
    }
}

////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////

void vow_window_create(int width, int height, const char* title)
{
    if (g_window.handle)
    {
        vow_log_print(VOW_LOG_LEVEL_WARNING, "Refused to create window. Window already exists.");
        return;
    }
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
    {
        vow_log_print(VOW_LOG_LEVEL_FATAL, "Failed to initialize GLFW.");
        vow_window_destroy();
        exit(0);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    g_window.handle = glfwCreateWindow(width, height, title, (void*) 0, (void*) 0);
    if (!g_window.handle)
    {
        vow_log_print(VOW_LOG_LEVEL_FATAL, "Failed to create window.");
        vow_window_destroy();
        exit(0);
    }
    const int context_version_major = glfwGetWindowAttrib(g_window.handle, GLFW_CONTEXT_VERSION_MAJOR);
    const int context_version_minor = glfwGetWindowAttrib(g_window.handle, GLFW_CONTEXT_VERSION_MINOR);
    if (context_version_major != 4 || context_version_minor != 6)
    {
        vow_log_print(VOW_LOG_LEVEL_FATAL, "Failed to create a valid OpenGL 4.6 context.");
        vow_window_destroy();
        exit(0);
    }
    glfwMakeContextCurrent(g_window.handle);
    (void) gladLoadGL(glfwGetProcAddress);
    glfwSetWindowCloseCallback(g_window.handle, close_callback);
    glfwSetWindowSizeCallback(g_window.handle, size_callback);
    vow_window_vsync(1);
}

void vow_window_destroy(void)
{
    glfwDestroyWindow(g_window.handle);
    glfwTerminate();
    g_window = (VowWindow) { 0 };
}

void vow_window_close(void)
{
    glfwSetWindowShouldClose(g_window.handle, GLFW_TRUE);
}

void vow_window_close_callback(void (*callback)(void))
{
    g_window.close_callback = callback;
}

void vow_window_position(int x, int y)
{
    glfwSetWindowPos(g_window.handle, x, y);
}

void vow_window_position_callback(void (*callback)(int x, int y))
{
    g_window.position_callback = callback;
}

void vow_window_size(int width, int height)
{
    glfwSetWindowSize(g_window.handle, width, height);
}

void vow_window_size_callback(void (*callback)(int width, int height))
{
    g_window.size_callback = callback;
}

void vow_window_title(const char* title)
{
    glfwSetWindowTitle(g_window.handle, title);
}

void vow_window_vsync(int flag)
{
    glfwSwapInterval(flag ? 1 : 0);
}

int vow_window_query_close(void)
{
    return glfwWindowShouldClose(g_window.handle);
}

VowTuple2i vow_window_query_position(void)
{
    VowTuple2i position;
    glfwGetWindowPos(g_window.handle, &position.x, &position.y);
    return position;
}

VowTuple2i vow_window_query_content_size(void)
{
    VowTuple2i content_size;
    glfwGetWindowSize(g_window.handle, &content_size.x, &content_size.y);
    return content_size;
}

VowTuple2i vow_window_query_frame_size(void)
{
    const VowTuple2i content_size = vow_window_query_content_size();
    int left, top, right, bottom;
    glfwGetWindowFrameSize(g_window.handle, &left, &right, &top, &bottom);
    const VowTuple2i frame_size =
    {
        content_size.x + left + right,
        content_size.y + top + bottom
    };
    return frame_size;
}