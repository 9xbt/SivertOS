#pragma once

#include <gfx/fb.h>
#include <ui/control.h>

typedef struct window_t window_t;

struct window_t {
    fb_t* contents;
    i32 x;
    i32 y;
    char* title;
    void(*paint)(window_t*);
    u8 style;
    control_t* controls[16];
    u64 control_count;
};

enum {
    WM_NONE = 0,
    WM_TITLEBAR = 1,
    WM_BORDER = 2,
    WM_CLOSABLE = 4,
    WM_RESIZABLE = 8,
    WM_MINIMIZABLE = 16,
    WM_MAXIMIZABLE = 32,
};

window_t* wnd_create_new(u32 width, u32 height, char* title, u8 style);
void wnd_destroy(window_t* wnd);
void wnd_add_control(window_t* wnd, control_t* ctl);
void wnd_remove_control(window_t* wnd, control_t* ctl);