#pragma once

#include <gfx/fb.h>

typedef struct control_t control_t;

struct control_t {
    fb_t* contents;
    i32 x;
    i32 y;
    char* name;
    char* text;
    void(*update)();
    void(*clicked)();
};

control_t* ctl_create_new(u32 width, u32 height, char* name, char* text);
void ctl_destroy(control_t* ctl);