#include <tools/shell/paint.h>

void shell_cmd_paint(int argc, char** argv) {
    memset(vbe_addr, 0, vbe_pitch * vbe_height);

    flanterm_write(flanterm_context, "\033[H\033[?25l", 9);
    printf("Simple paint program - Press any key to exit");

    while (kb_get_char() == 0) {
        if (!mouse_state.current.left && !mouse_state.current.right)
            vbe_addr[mouse_state.last.y * vbe_width + mouse_state.last.x] = 0x00000000; // clean up old cursor

        if (mouse_state.current.left || mouse_state.current.right)
            cv_draw_line(vbe_addr, vbe_width, mouse_state.last.x, mouse_state.last.y, mouse_state.current.x, mouse_state.current.y, mouse_state.current.left ? 0xFFFFFFFF : 0); // draw the line
        else
            vbe_addr[mouse_state.current.y * vbe_width + mouse_state.current.x] = 0xFFFFFFFF; // draw new cursor
    }

    memset(vbe_addr, 0, vbe_pitch * vbe_height);
    flanterm_write(flanterm_context, "\033[H\033[2J\033[?25h", 13);
}