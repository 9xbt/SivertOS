#pragma once

#include <gfx/fb.h>

typedef struct window_t window_t;

struct window_t {
    fb_t* contents;
    i32 x;
    i32 y;
    char* title;
    void(*paint)(window_t*);
};

window_t* wnd_create_new(u32 width, u32 height, char* title);
void wnd_destroy(window_t* wnd);