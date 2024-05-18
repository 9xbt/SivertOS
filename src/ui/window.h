#pragma once

#include <gfx/fb.h>

typedef struct {
    fb_t* contents;
    i32 x;
    i32 y;
    char* title;
} window_t;

window_t* wnd_create_new(u32 width, u32 height, char* title);
void wnd_destroy(window_t* wnd);