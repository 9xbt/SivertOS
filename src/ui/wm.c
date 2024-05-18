#include <ui/wm.h>
#include <gfx/fb.h>
#include <gfx/font.h>
#include <gfx/canvas.h>
#include <ui/resources.h>
#include <drivers/kb.h>
#include <drivers/mouse.h>
#include <kernel/kernel.h>

fb_t* wm_mouse_cursor;
font_t* wm_default_font;

window_t* wm_windows[16];
u64 wm_window_count = 0;

void wm_init() {
    wm_mouse_cursor = fb_create(21, 21, (u32*)wm_mouse_rawdata);
    wm_default_font = font_create((u8*)wm_font_rawdata, 8, 8);

    cv_clear(back_fb, 0xFFFFFF);
}

void wm_update() {
    // remove old cursor
    cv_draw_filled_rectangle(back_fb, mouse_state.last.x - 48, mouse_state.last.y - 48, 96, 96, 0xFFFFFF);
    // draw new cursor
    cv_draw_image_alpha(back_fb, wm_mouse_cursor, mouse_state.current.x, mouse_state.current.y);

    cv_draw_string(back_fb, wm_default_font, 300, 300, "hello world\n", 0);

    memcpy(front_fb->address, back_fb->address, front_fb->pitch * front_fb->height);
}

void wm_add_window(window_t* wnd) {
    wm_windows[wm_window_count] = wnd;
    wm_window_count++;
}

void wm_remove_window(window_t* wnd) {
    for (u64 i = 0; i < sizeof(wm_windows); i++)
        if (wm_windows[i] == wnd) {
            for (u64 o = i; i < wm_window_count - 1; i++)
                wm_windows[i] = wm_windows[i + 1];
            break;
        }
}