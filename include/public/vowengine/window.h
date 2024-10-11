#ifndef VOWENGINE_GUARD_WINDOW
#define VOWENGINE_GUARD_WINDOW

////////////////////////////////////////////////////////////////////////////////
// Dependencies
////////////////////////////////////////////////////////////////////////////////

#include <vowengine/tuple.h>

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

void vow_window_create(int width, int height, const char* title);
void vow_window_destroy(void);
void vow_window_close(void);
void vow_window_close_callback(void (*callback)(void));
void vow_window_position(int x, int y);
void vow_window_position_callback(void (*callback)(int x, int y));
void vow_window_size(int width, int height);
void vow_window_size_callback(void (*callback)(int width, int height));
void vow_window_title(const char* title);
void vow_window_vsync(int flag);

int vow_window_query_close(void);
VowTuple2i vow_window_query_position(void);
VowTuple2i vow_window_query_content_size(void);
VowTuple2i vow_window_query_frame_size(void);

#endif