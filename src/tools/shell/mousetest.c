#include <tools/shell/mousetest.h>

void shell_cmd_mousetest(int argc, char** argv) {
    memset(vbe_addr, 0, vbe_pitch * vbe_height);

    while (kb_get_char() == 0) {
        asm ("cli");

        if (!mouse_state.current.left && !mouse_state.current.right)
            vbe_addr[mouse_state.last.y * vbe_width + mouse_state.last.x] = 0x00000000; // clean up old cursor

        if (mouse_state.current.left || mouse_state.current.right)
            cv_draw_line(vbe_addr, vbe_width, mouse_state.last.x, mouse_state.last.y, mouse_state.current.x, mouse_state.current.y, mouse_state.current.left ? 0xFFFFFFFF : 0); // draw the line
        else
            vbe_addr[mouse_state.current.y * vbe_width + mouse_state.current.x] = 0xFFFFFFFF; // draw new cursor

        asm ("sti");
    }
}