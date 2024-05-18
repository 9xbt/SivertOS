#pragma once

#include <types.h>
#include <gfx/fb.h>
#include <gfx/font.h>

void cv_clear(fb_t* fb, u32 color);
void cv_copy_portion(fb_t* dest, fb_t* src, u32 x, u32 y, u32 width, u32 height);
void cv_draw_line(fb_t* fb, u32 x1, u32 y1, u32 x2, u32 y2, u32 color);
void cv_draw_filled_rectangle(fb_t* fb, i32 x, i32 y, u32 width, u32 height, u32 color);
void cv_draw_image(fb_t* fb, i32 x, i32 y, fb_t* bmp);
void cv_draw_image_alpha(fb_t* fb, fb_t* bmp, i32 x, i32 y);
void cv_draw_string(fb_t* fb, font_t* font, i32 x, i32 y, char* str, u32 color);