#include <ui/apps/rezisetest.h>
#include <kernel/kernel.h>
#include <ui/window.h>
#include <ui/wm.h>
#include <gfx/font.h>
#include <gfx/canvas.h>
#include <drivers/rtc.h>
#include <lib/libc.h>

bool width_increase = true;

void resize_start() {
    window_t* wnd = wnd_create_new(70, 70, "resizetest", WM_NONE);
    wnd->paint = resize_paint;
    wnd->x = 20;
    wnd->y = 20;
    wm_add_window(wnd);
}

void resize_paint(window_t* wnd) {
    cv_draw_filled_rectangle(back_fb, wnd->x, wnd->y, wnd->contents->width, wnd->contents->height, 0x000000);

    if (width_increase) {
        fb_update_size(wnd->contents, wnd->contents->width + 1, wnd->contents->height - 1);

        if (wnd->contents->width == 120) width_increase = false;
    }
    else {
        fb_update_size(wnd->contents, wnd->contents->width - 1, wnd->contents->height + 1);

        if (wnd->contents->width == 20) width_increase = true;
    }

    cv_draw_filled_rectangle(wnd->contents, 0, 0, wnd->contents->width, wnd->contents->height, 0xc0c0c0);
}