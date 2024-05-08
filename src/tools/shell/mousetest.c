#include <tools/shell/mousetest.h>

void shell_cmd_mousetest(int argc, char** argv) {
    while (kb_get_char() == 0) {
        vbe_addr[mouse_last_y * vbe_width + mouse_last_x] = 0x00000000;
        vbe_addr[mouse_y * vbe_width + mouse_x] = 0xFFFFFFFF;
    }
}