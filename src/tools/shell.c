#include <tools/shell.h>

const int shell_cmds_len = 3;

const char *shell_cmds[] = {
    "help",
    "clear",
    "mousetest"
};

const char *shell_cmd_descriptions[] = {
    "Shows this page",
    "Clears the screen",
    "Test command for the mouse driver"
};

void *shell_cmd_handlers[] = {
    shell_cmd_help,
    shell_cmd_clear,
    shell_cmd_mousetest
};

void shell_exec() {
    printf("$ ");

    char input[256];
    kb_get_string(input, 256);

    if (!strcmp(input, "")) {
        return;
    }

    for (int i = 0; i < shell_cmds_len; i++) {
        if (!strcmp(input, shell_cmds[i])) {
            void(*handler)(int, char**);

            handler = shell_cmd_handlers[i];

            if (shell_cmd_handlers[i] != NULL)
                handler(0, NULL);

            return;
        }
    }

    printf("%s: command not found\n", input);
}