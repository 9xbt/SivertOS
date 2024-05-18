#pragma once

#include <types.h>

typedef struct {
    u8* data;
    u8  width;
    u8  height;
} font_t;

font_t* font_create(u8* data, u8 width, u8 height);
void font_destroy(font_t* font);