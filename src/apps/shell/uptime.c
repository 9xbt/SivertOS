#include <apps/shell/uptime.h>

void shell_cmd_uptime(int argc, char **argv) {
    (void)(argc);
    (void)(argv);
    
    printf("Up %d seconds\n", (i32)seconds_since_boot());
}