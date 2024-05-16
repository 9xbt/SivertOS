#include <apps/shell/help.h>

void shell_cmd_help(int argc, char** argv) {
    (void)argc;
    (void)argv;

    for (int i = 0; i < shell_cmd_count; i++) {
        printf("%s : %s\n", shell_cmds[i], shell_cmd_descriptions[i]);
    }
}