#include <apps/shell/paint.h>

void shell_cmd_paint(int argc, char** argv) {
    (void)argc;
    (void)argv;
    
    fb_t* drawing = fb_create_new(back_fb->width, back_fb->height);
    cv_clear(drawing, 0xFFFFFF);

    while (kb_get_char() == 0) {
        if (mouse_state.current.left)
            cv_draw_line(drawing, mouse_state.last.x, mouse_state.last.y, mouse_state.current.x, mouse_state.current.y, 0); // draw the line
        else if (mouse_state.current.right)
            cv_draw_filled_rectangle(drawing, mouse_state.current.x - 12, mouse_state.current.y - 12, 25, 25, 0xFFFFFF); // erase stuff

        cv_draw_image(back_fb, 0, 0, drawing);
        cv_draw_image_alpha(back_fb, wm_mouse_cursor, mouse_state.current.x, mouse_state.current.y);
        memcpy(front_fb->address, back_fb->address, front_fb->pitch * front_fb->height);
    }

    fb_destroy(drawing);

    cv_clear(front_fb, 0x1b1c1b);
    flanterm_write(flanterm_context, "\033[H\033[2J\033[?25h", 13);
}