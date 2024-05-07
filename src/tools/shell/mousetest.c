#include <tools/shell/mousetest.h>

void shell_cmd_mousetest(int argc, char** argv) {
    printf("Mouse X: %d | Mouse Y: %d", mouse_x, mouse_y);
}