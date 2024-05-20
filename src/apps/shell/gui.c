#include <ui/wm.h>
#include <drivers/kb.h>
#include <gfx/canvas.h>
#include <kernel/kernel.h>

void shell_cmd_gui(int argc, char** argv) {
    while (kb_get_char() != 27) {
        wm_update();
    }

    cv_clear(front_fb, 0x1b1c1b);
}