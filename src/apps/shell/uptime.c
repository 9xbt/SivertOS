#include <apps/shell/uptime.h>

void shell_cmd_uptime(int argc, char **argv) {
    printf("Up %d seconds\n", seconds_since_boot());
}