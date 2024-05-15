#include <apps/shell/paint.h>

void shell_cmd_paint(int argc, char** argv) {
    (void)(argc);
    (void)(argv);

    memset(fb_addr, 0, framebuffer->pitch * framebuffer->height);

    flanterm_write(flanterm_context, "\033[H\033[?25l", 9);
    printf("Simple paint program - Press any key to exit");

    while (kb_get_char() == 0) {
        if (!mouse_state.current.left && !mouse_state.current.right)
            fb_addr[mouse_state.last.y * framebuffer->width + mouse_state.last.x] = 0x00000000; // clean up old cursor

        if (mouse_state.current.left || mouse_state.current.right)
            cv_draw_line(fb_addr, framebuffer->width, mouse_state.last.x, mouse_state.last.y, mouse_state.current.x, mouse_state.current.y, mouse_state.current.left ? 0xFFFFFFFF : 0); // draw the line
        else
            fb_addr[mouse_state.current.y * framebuffer->width + mouse_state.current.x] = 0xFFFFFFFF; // draw new cursor
    }

    memset(fb_addr, 0, framebuffer->pitch * framebuffer->height);
    flanterm_write(flanterm_context, "\033[H\033[2J\033[?25h", 13);
}