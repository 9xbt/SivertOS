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
#include <ui/apps/rezisetest.h>
#include <ui/apps/test.h>

fb_t* wm_mouse_cursor;
font_t* wm_default_font;

window_t* wm_windows[16];
u64 wm_window_count = 0;

void wm_init() {
    wm_mouse_cursor = fb_create(21, 21, (u32*)wm_mouse_rawdata);
    wm_default_font = font_create((u8*)wm_font_rawdata, 8, 16);

    cv_clear(back_fb, 0xFF000000);

    taskbar_start();
    test_start();

    // Only uncomment to see a window resizing example.
    // Do not leave it uncommented as it will memory leak (or just use all of the meory somehow) and slow down and otherwise break everything else in the process.
    //resize_start();
}

void wm_update() {
    cv_draw_filled_rectangle(back_fb, mouse_state.last.x, mouse_state.last.y, 21, 21, 0x000000); // remove old cursor

    cv_draw_string(back_fb, wm_default_font, back_fb->width - 200, back_fb->height - 44, "For testing purposes only", 0xFFFFFF);

    for (int i = 0; i < wm_window_count; i++) {
        wm_windows[i]->paint(wm_windows[i]);
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

void wm_paint_window(window_t* wnd) {
    // Render & preform logic for controls
    for (int i = 0; i < wnd->control_count; i++) {
        wnd->controls[i]->update(wnd->controls[i]);
        cv_draw_image(wnd->contents, wnd->controls[i]->x, wnd->controls[i]->y, wnd->controls[i]->contents);
    }

    if (wnd->style & WM_NONE) return;

    if (wnd->style & WM_BORDER) {
        // Draw the outermost border lines
        cv_draw_line(wnd->contents, 0, 0, 0, wnd->contents->height, 0xDFDFDF);
        cv_draw_line(wnd->contents, 0, 0, wnd->contents->width, 0, 0xDFDFDF);
        cv_draw_line(wnd->contents, wnd->contents->width - 1, wnd->contents->height - 1, 0, wnd->contents->height - 1, 0xDFDFDF);
        cv_draw_line(wnd->contents, wnd->contents->width - 1, wnd->contents->height - 1, wnd->contents->width - 1, 0, 0xDFDFDF);

        // Draw the second most out border lines
        cv_draw_line(wnd->contents, 1, 1, 1, wnd->contents->height - 1, 0xFFFFFF);
        cv_draw_line(wnd->contents, 1, 1, wnd->contents->width - 2, 1, 0xFFFFFF);
        cv_draw_line(wnd->contents, wnd->contents->width - 2, wnd->contents->height - 2, 1, wnd->contents->height - 2, 0xFFFFFF);
        cv_draw_line(wnd->contents, wnd->contents->width - 2, wnd->contents->height - 2, wnd->contents->width - 2, 0, 0xFFFFFF);

        // Draw the two innermost lines (rectangles?)
        cv_draw_filled_rectangle(wnd->contents, 2, 2, 2, wnd->contents->height - 5, 0xC0C0C0); // Vertical rect
        cv_draw_filled_rectangle(wnd->contents, 2, 2, wnd->contents->width - 5, 2, 0xC0C0C0); // Horizontal rect
        cv_draw_filled_rectangle(wnd->contents, wnd->contents->width - 4, 2, 2, wnd->contents->height - 5, 0xC0C0C0); // Vertical rect 2
        cv_draw_filled_rectangle(wnd->contents, 2, wnd->contents->height - 4, wnd->contents->width - 4, 2, 0xC0C0C0); // Horizontal rect 2
    }

    if (wnd->style & WM_TITLEBAR) {
        cv_draw_filled_rectangle(wnd->contents, 4, 4,  wnd->contents->width - 8, 18, 0x000180 /*0xDB0D14*/); // Title bar background
        cv_draw_string(wnd->contents, wm_default_font, 7, 6, wnd->title, 0xFFFFFF); // Window title text
    }

    if (wnd->style & WM_MINIMIZABLE) {
        // Do this later
    }

    if (wnd->style & WM_MAXIMIZABLE) {
        // Do this slightly less later
    }

    if (wnd->style & WM_CLOSABLE) {
        // Do this the least later, once buttons are a thing
    }

    if (wnd->style & WM_RESIZABLE) {
        // This would be easy but i dont wanna do it right now
    }
}