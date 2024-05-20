#pragma once

#include <types.h>
#include <ui/window.h>
#include <gfx/font.h>

extern fb_t* wm_mouse_cursor;
extern font_t* wm_default_font;

void wm_init();
void wm_update();
void wm_add_window(window_t* wnd);
void wm_remove_window(window_t* wnd);
void wm_paint_window(window_t* wnd);