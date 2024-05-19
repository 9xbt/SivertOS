#pragma once

#include <types.h>

typedef struct {
    u32* address;
    u32  width;
    u32  height;
    u32  pitch;
} fb_t;

fb_t* fb_create(u32 width, u32 height, u32* fb_address);

fb_t* fb_create_new(u32 width, u32 height);

void fb_update_size(fb_t* fb, u32 width, u32 height);

void fb_destroy(fb_t* fb);