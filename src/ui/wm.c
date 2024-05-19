#include <ui/wm.h>
#include <gfx/fb.h>
#include <gfx/font.h>
#include <gfx/canvas.h>
#include <drivers/kb.h>
#include <drivers/rtc.h>
#include <drivers/mouse.h>
#include <kernel/kernel.h>
#include <ui/resources.h>
#include <ui/apps/system/taskbar.h>

fb_t* wm_mouse_cursor;
font_t* wm_default_font;

window_t* wm_windows[16];
u64 wm_window_count = 0;

void wm_init() {
    wm_mouse_cursor = fb_create(21, 21, (u32*)wm_mouse_rawdata);
    wm_default_font = font_create((u8*)wm_font_rawdata, 8, 16);

    cv_clear(back_fb, 0xFFFFFF);

    taskbar_start();
}

void wm_update() {
    cv_draw_filled_rectangle(back_fb, mouse_state.last.x - 48, mouse_state.last.y - 48, 96, 96, 0xFFFFFF); // remove old cursor

    cv_draw_string(back_fb, wm_default_font, back_fb->width - 200, back_fb->height - 44, "For testing purposes only", 0);

    for (int i = 0; i < wm_window_count; i++) {
        cv_draw_image(back_fb, wm_windows[i]->x, wm_windows[i]->y, wm_windows[i]->contents);
    }

    cv_draw_image_alpha(back_fb, wm_mouse_cursor, mouse_state.current.x, mouse_state.current.y); // draw new cursor

    memcpy(front_fb->address, back_fb->address, front_fb->pitch * front_fb->height);
}

void wm_add_window(window_t* wnd) {
    if (wm_window_count > 16) return;
    wm_windows[wm_window_count] = wnd;
    wm_window_count++;
    wnd->paint(wnd);
}

void wm_remove_window(window_t* wnd) {
    for (u64 i = 0; i < sizeof(wm_windows); i++)
        if (wm_windows[i] == wnd) {
            for (u64 o = i; i < wm_window_count - 1; i++)
                wm_windows[i] = wm_windows[i + 1];
            break;
        }
}