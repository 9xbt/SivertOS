#include <apps/shell.h>

const int shell_cmd_count = 7;

const char *shell_cmds[] = {
    "help",
    "clear",
    "date",
    "uptime",
    "paint",
    "ls",
    "cat",
    "crash",
};

const char *shell_cmd_descriptions[] = {
    "Shows this page",
    "Clears the screen",
    "Displays the date and time",
    "Displays how long the system has been running",
    "Simple paint program to test the mouse driver",
    "Lists the files in the current directory",
    "Prints the contents of a file",
    "As its name suggests, crashes the OS"
};

const void *shell_cmd_handlers[] = {
    shell_cmd_help,
    shell_cmd_clear,
    shell_cmd_date,
    shell_cmd_uptime,
    shell_cmd_paint,
    shell_cmd_ls,
    shell_cmd_cat,
    shell_cmd_crash
};

char** str_split(char* input_string, const char delimiter, int* num_tokens);

void shell_exec() {
    const char prompt[] = "\033[91msivert\033[94m / # \033[0m";
    flanterm_write(flanterm_context, prompt, sizeof(prompt));

    char input[256];
    kb_get_string(input, sizeof(input));

    if (!strcmp(input, "")) {
        return;
    }

    for (int i = 0; i < shell_cmd_count; i++) {
        if (!strncmp(input, shell_cmds[i], strlen(shell_cmds[i]))) {
            void(*handler)(int, char**);

            handler = shell_cmd_handlers[i];

            char** args;
            args[0] = input;

            if (shell_cmd_handlers[i] != NULL)
                handler(1, args);

            return;
        }
    }

    printf("%s: command not found\n", input);
}