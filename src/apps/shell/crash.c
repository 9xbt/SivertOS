#include <apps/shell/crash.h>

void shell_cmd_crash(int argc, char** argv) {
    (void)argc;
    (void)argv;

    panic("MANUALLY_INITIATED_CRASH");
}