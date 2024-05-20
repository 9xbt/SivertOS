#include <gfx/fb.h>
#include <ui/wm.h>
#include <ui/window.h>
#include <lib/alloc.h>
#include <ui/control.h>

window_t* wnd_create_new(u32 width, u32 height, char* title, u8 style) {
    window_t* wnd = (window_t*)kmalloc(sizeof(window_t));
    wnd->contents = fb_create_new(width, height);
    wnd->x = 50;
    wnd->y = 50;
    wnd->title = title;
    wnd->style = style;
    wnd->control_count = 0;

    return wnd;
}

void wnd_destroy(window_t* wnd) {
    wm_remove_window(wnd);
    fb_destroy(wnd->contents);
    kfree(wnd);
}

void wnd_add_control(window_t* wnd, control_t* ctl) {
    if (wnd->control_count > 16) return;
    wnd->controls[wnd->control_count] = ctl;
    wnd->control_count++;
    wnd->paint(wnd);
}

void wnd_remove_control(window_t* wnd, control_t* ctl) {
    for (u64 i = 0; i < sizeof(wnd->controls); i++)
        if (wnd->controls[i] == ctl) {
            for (u64 o = i; i < wnd->control_count - 1; i++)
                wnd->controls[i] = wnd->controls[i + 1];
            break;
        }
}