#include <vowframework/private/log.h>
#include <vowframework/private/shader.h>

#include <vowframework/file.h>
#include <vowframework/handle.h>
#include <vowframework/log.h>
#include <vowframework/memory.h>
#include <vowframework/shader.h>

#include <glad/gl.h>

typedef struct VowShader
{
    VowHandle handle;
    GLuint vertex_object;
    GLuint fragment_object;
    GLuint program;
    char* vertex_text;
    char* fragment_text;
}
VowShader;

typedef struct VowShaderData
{
    VowShader* shaders;
    int count;
}
VowShaderData;

static VowShaderData vow_shader_data = { 0 };

void vow_shader_initialize(void)
{
    vow_shader_data.shaders = vow_memory_allocate(VOW_SHADER_CAPACITY * sizeof(VowShader));
    vow_shader_data.count = 1;
}

void vow_shader_finalize(void)
{
    vow_memory_free(vow_shader_data.shaders);
    vow_shader_data = (VowShaderData) { 0 };
}

void vow_shader_update(float frameTime) {}

void vow_shader_bind(VowHandle handle)
{
    glUseProgram(vow_shader_data.shaders[handle].program);
}

void vow_shader_unbind(void)
{
    glUseProgram(0);
}

VowHandle vow_shader_create(const char* vertex_path, const char* fragment_path)
{
    const VowHandle handle = ++vow_shader_data.count;
    if (handle == VOW_HANDLE_INVALID)
    {
        vow_log_print(VOW_LOG_LEVEL_ERROR, "Failed to create shader.");
        vow_shader_destroy(handle);
        return VOW_HANDLE_INVALID;
    }
    vow_shader_data.shaders[handle].vertex_object = glCreateShader(GL_VERTEX_SHADER);
    if (!vow_shader_data.shaders[handle].vertex_object)
    {
        vow_log_print(VOW_LOG_LEVEL_ERROR, "Failed to create vertex object.");
        vow_shader_destroy(handle);
        return VOW_HANDLE_INVALID;
    }
    vow_shader_data.shaders[handle].fragment_object = glCreateShader(GL_FRAGMENT_SHADER);
    if (!vow_shader_data.shaders[handle].fragment_object)
    {
        vow_log_print(VOW_LOG_LEVEL_ERROR, "Failed to create fragment object.");
        vow_shader_destroy(handle);
        return VOW_HANDLE_INVALID;
    }
    const char* vertex_text = vow_file_read(vertex_path);
    if (!vertex_text)
    {
        vow_log_print(VOW_LOG_LEVEL_ERROR, "Failed to read vertex text: %s", vertex_path);
        vow_shader_destroy(handle);
        return VOW_HANDLE_INVALID;
    }
    const char* fragment_text = vow_file_read(fragment_path);
    if (!fragment_text)
    {
        vow_log_print(VOW_LOG_LEVEL_ERROR, "Failed to read fragment text: %s", fragment_path);
        vow_shader_destroy(handle);
        return VOW_HANDLE_INVALID;
    }
    const char* vertex_text_const = vow_shader_data.shaders[handle].vertex_text;
    const char* fragment_text_const = vow_shader_data.shaders[handle].fragment_text;
    glShaderSource(vow_shader_data.shaders[handle].vertex_object, 1, &vertex_text_const, (void*) 0);
    glShaderSource(vow_shader_data.shaders[handle].fragment_object, 1, &fragment_text_const, (void*) 0);
    glCompileShader(vow_shader_data.shaders[handle].vertex_object);
    GLint vertex_compile_status;
    glGetShaderiv(vow_shader_data.shaders[handle].vertex_object, GL_COMPILE_STATUS, &vertex_compile_status);
    if (!vertex_compile_status)
    {
        vow_log_print(VOW_LOG_LEVEL_ERROR, "Failed to compile vertex shader.");
        vow_shader_destroy(handle);
        return VOW_HANDLE_INVALID;
    }
    glCompileShader(vow_shader_data.shaders[handle].fragment_object);
    GLint fragment_compile_status;
    glGetShaderiv(vow_shader_data.shaders[handle].fragment_object, GL_COMPILE_STATUS, &fragment_compile_status);
    if (!fragment_compile_status)
    {
        vow_log_print(VOW_LOG_LEVEL_ERROR, "Failed to compile fragment shader.");
        vow_shader_destroy(handle);
        return VOW_HANDLE_INVALID;
    }
    vow_shader_data.shaders[handle].program = glCreateProgram();
    if (!vow_shader_data.shaders[handle].program)
    {
        vow_log_print(VOW_LOG_LEVEL_ERROR, "Failed to create shader program.");
        vow_shader_destroy(handle);
        return VOW_HANDLE_INVALID;
    }
    glAttachShader(vow_shader_data.shaders[handle].program, vow_shader_data.shaders[handle].vertex_object);
    glAttachShader(vow_shader_data.shaders[handle].program, vow_shader_data.shaders[handle].fragment_object);
    glLinkProgram(vow_shader_data.shaders[handle].program);
    GLint program_link_status;
    glGetProgramiv(vow_shader_data.shaders[handle].program, GL_LINK_STATUS, &program_link_status);
    if (!program_link_status)
    {
        vow_log_print(VOW_LOG_LEVEL_ERROR, "Failed to link shader program.");
        vow_shader_destroy(handle);
        return VOW_HANDLE_INVALID;
    }
    return handle;
}

void vow_shader_destroy(VowHandle handle)
{
    if (vow_shader_data.shaders[handle].vertex_object)
    {
        glDeleteShader(vow_shader_data.shaders[handle].vertex_object);
    }
    if (vow_shader_data.shaders[handle].fragment_object)
    {
        glDeleteShader(vow_shader_data.shaders[handle].fragment_object);
    }
    if (vow_shader_data.shaders[handle].program)
    {
        glDeleteProgram(vow_shader_data.shaders[handle].program);
    }
    if (vow_shader_data.shaders[handle].vertex_text)
    {
        vow_memory_free(vow_shader_data.shaders[handle].vertex_text);
    }
    if (vow_shader_data.shaders[handle].fragment_text)
    {
        vow_memory_free(vow_shader_data.shaders[handle].fragment_text);
    }
    vow_shader_data.shaders[handle] = (VowShader) { 0 };
    vow_shader_data.count--;
}