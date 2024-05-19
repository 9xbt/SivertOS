#include <gfx/fb.h>
#include <ui/wm.h>
#include <ui/window.h>
#include <lib/alloc.h>

window_t* wnd_create_new(u32 width, u32 height, char* title, u8 style) {
    window_t* wnd = (window_t*)kmalloc(sizeof(window_t));
    wnd->contents = fb_create_new(width, height);
    wnd->x = 50;
    wnd->y = 50;
    wnd->title = title;
    wnd->style = style;

    return wnd;
}

void wnd_destroy(window_t* wnd) {
    wm_remove_window(wnd);
    fb_destroy(wnd->contents);
    kfree(wnd);
}