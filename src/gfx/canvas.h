#pragma once

#include <types.h>
#include <lib/libc.h>
#include <lib/math.h>

void cv_clear(u32* fb, u32 width, u32 fb_height, u32 color);
void cv_draw_line(u32* fb, u32 fb_width, u32 fb_height, u32 x1, u32 y1, u32 x2, u32 y2, u32 color);