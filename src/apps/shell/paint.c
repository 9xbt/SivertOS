#include <apps/shell/paint.h>

void shell_cmd_paint(int argc, char** argv) {
    (void)argc;
    (void)argv;
    
    cv_clear(front_fb, 0x000000);

    while (kb_get_char() == 0) {
        if (!mouse_state.current.left && !mouse_state.current.right)
            front_fb->address[mouse_state.last.y * framebuffer->width + mouse_state.last.x] = 0x000000; // clean up old cursor

        if (mouse_state.current.left || mouse_state.current.right)
            cv_draw_line(front_fb, mouse_state.last.x, mouse_state.last.y, mouse_state.current.x, mouse_state.current.y, mouse_state.current.left ? 0xFFFFFFFF : 0); // draw the line
        else
            front_fb->address[mouse_state.current.y * framebuffer->width + mouse_state.current.x] = 0xFFFFFF; // draw new cursor
    }

    cv_clear(front_fb, 0x1b1c1b);
    flanterm_write(flanterm_context, "\033[H\033[2J\033[?25h", 13);
}