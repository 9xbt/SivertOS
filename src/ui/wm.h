#pragma once

#include <types.h>
#include <ui/window.h>

void wm_init();
void wm_update();
void wm_add_window(window_t* wnd);
void wm_remove_window(window_t* wnd);