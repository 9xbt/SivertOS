#pragma once

#include <ui/control.h>
#include <ui/window.h>
#include <gfx/canvas.h>

void button_new(window_t* wnd, i32 x, i32 y, u32 width, u32 height, char* name, char* text, void* clicked);
void button_update(control_t* ctl);