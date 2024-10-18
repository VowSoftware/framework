#ifndef VOW_GUARD_SHADER
#define VOW_GUARD_SHADER

#include <vowframework/handle.h>

////////////////////////////////////////////////////////////////////////////////
// Creates a timer.
//
// Parameters
//   * `vertex_path`: Absolute path to a vertex shader file.
//   * `fragment_path`: Absolute path to a fragment shader file.
//
// Fails
//   * Amount of shaders created exceeds `VOW_SHADER_CAPACITY`.
//
// Returns
//   * [Success] Handle to the created shader.
//   * [Failure] `VOW_HANDLE_INVALID`
////////////////////////////////////////////////////////////////////////////////
VowHandle vow_shader_create(const char* vertex_path, const char* fragment_path);

////////////////////////////////////////////////////////////////////////////////
// Destroys a shader.
//
// Parameters
//   * `handle`: The shader's handle.
////////////////////////////////////////////////////////////////////////////////
void vow_shader_destroy(VowHandle handle);

#endif