#include <tools/shell/clear.h>

void shell_cmd_clear(int argc, char** argv) {
    flanterm_write(flanterm_context, "\033[2J\033[H", 7);
}