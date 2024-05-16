#include <apps/shell.h>

const int shell_cmd_count = 6;

const char *shell_cmds[] = {
    "help",
    "clear",
    "date",
    "uptime",
    "paint",
    "crash",
};

const char *shell_cmd_descriptions[] = {
    "Shows this page",
    "Clears the screen",
    "Displays the date and time",
    "Displays how long the system has been running",
    "Simple paint program to test the mouse driver",
    "As its name suggests, crashes the OS"
};

const void *shell_cmd_handlers[] = {
    shell_cmd_help,
    shell_cmd_clear,
    shell_cmd_date,
    shell_cmd_uptime,
    shell_cmd_paint,
    shell_cmd_crash
};

void shell_exec() {
    const char prompt[] = "\033[91msivert\033[94m # \033[0m";
    flanterm_write(flanterm_context, prompt, sizeof(prompt));

    char input[256];
    kb_get_string(input, sizeof(input));

    if (!strcmp(input, "")) {
        return;
    }

    for (int i = 0; i < shell_cmd_count; i++) {
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