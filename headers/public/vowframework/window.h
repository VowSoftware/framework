#ifndef VOW_GUARD_WINDOW
#define VOW_GUARD_WINDOW

#include <vowframework/tuple.h>

#include <stdbool.h>

void vow_window_create(int width, int height, const char* title);
void vow_window_destroy(void);
void vow_window_close(void);
void vow_window_close_callback(void (*callback)(void));
void vow_window_position(int x, int y);
void vow_window_position_callback(void (*callback)(int x, int y));
void vow_window_size(int width, int height);
void vow_window_size_callback(void (*callback)(int width, int height));
void vow_window_title(const char* title);
void vow_window_vsync(bool flag);

bool vow_window_should_close(void);
VowTuple2i vow_window_get_position(void);
VowTuple2i vow_window_get_content_size(void);
VowTuple2i vow_window_get_frame_size(void);

#endif