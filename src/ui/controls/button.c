#include <ui/controls/button.h>
#include <ui/control.h>
#include <ui/window.h>
#include <ui/wm.h>
#include <gfx/canvas.h>

void button_new(window_t* wnd, i32 x, i32 y, u32 width, u32 height, char* name, char* text, void* clicked) {
    control_t* ctl = ctl_create_new(width, height, name, text);
    ctl->x = x;
    ctl->y = y;
    ctl->update = button_update;
    ctl->clicked = clicked;

    wnd_add_control(wnd, ctl);
}

void button_update(control_t* ctl) {
    cv_clear(ctl->contents, 0xC0C0C0);

    cv_draw_string(ctl->contents, wm_default_font, 4, ctl->contents->height / 2 - 7, ctl->text, 0x000000);

    cv_draw_line(ctl->contents, 0, 0, ctl->contents->width - 1, 0, 0xFFFFFF);
    cv_draw_line(ctl->contents, 0, 0, 0, ctl->contents->height - 1, 0xFFFFFF);

    cv_draw_line(ctl->contents, 1, 1, ctl->contents->width - 2, 1, 0xDFDFDF);
    cv_draw_line(ctl->contents, 1, 1, 1, ctl->contents->height - 2, 0xDFDFDF);

    cv_draw_line(ctl->contents, ctl->contents->width - 1, 0, ctl->contents->width - 1, ctl->contents->height, 0x000000);
    cv_draw_line(ctl->contents, 0, ctl->contents->height - 1, ctl->contents->width - 1, ctl->contents->height - 1, 0x000000);

    cv_draw_line(ctl->contents, ctl->contents->width - 2, 1, ctl->contents->width - 2, ctl->contents->height - 1, 0x808080);
    cv_draw_line(ctl->contents, 1, ctl->contents->height - 2, ctl->contents->width - 2, ctl->contents->height - 2, 0x808080);
} 