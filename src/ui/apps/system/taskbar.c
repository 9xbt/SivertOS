#include <ui/apps/system/taskbar.h>
#include <kernel/kernel.h>
#include <ui/window.h>
#include <ui/wm.h>
#include <gfx/font.h>
#include <gfx/canvas.h>
#include <drivers/rtc.h>
#include <lib/libc.h>

void taskbar_start() {
    window_t* wnd = wnd_create_new(back_fb->width, 28, "taskbar");
    wm_add_window(wnd);
}

void taskbar_paint(window_t* wnd) {
    char h[3];
    char m[3];
    itoa(h, 10, rtc_hour());
    itoa(m, 10, rtc_minute());
    if (h[1] == 0) {
        h[1] = h[0];
        h[0] = '0';
    }
    if (m[1] == 0) {
        m[1] = m[0];
        m[0] = '0';
    }

    cv_draw_filled_rectangle(wnd->contents, 0, wnd->contents->height - 28, wnd->contents->width, 28, 0xc0c0c0);
    cv_draw_string(wnd->contents, wm_default_font, wnd->contents->width - 46, wnd->contents->height - 22, h, 0);
    cv_draw_string(wnd->contents, wm_default_font, wnd->contents->width - 30, wnd->contents->height - 22, ":", 0);
    cv_draw_string(wnd->contents, wm_default_font, wnd->contents->width - 22, wnd->contents->height - 22, m, 0);
}