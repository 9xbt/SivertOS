#include <tools/shell.h>

const char *shell_cmds[] = {
    "help",
    "clear",
    "paint"
};

const char *shell_cmd_descriptions[] = {
    "Shows this page",
    "Clears the screen",
    "Simple paint program to test the mouse driver"
};

void *shell_cmd_handlers[] = {
    shell_cmd_help,
    shell_cmd_clear,
    shell_cmd_paint
};

void shell_exec() {
    const char prompt[] = "\033[91msivert\033[94m # \033[0m";
    flanterm_write(flanterm_context, prompt, sizeof(prompt));

    char input[256];
    kb_get_string(input, 256);

    if (!strcmp(input, "")) {
        return;
    }

    for (int i = 0; i < 3; i++) {
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