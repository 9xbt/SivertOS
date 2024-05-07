#include <tools/shell.h>

const int shell_cmds_len = 3;

const char *shell_cmds[] = {
    "help",
    "clear",
    "mousetest"
};

const char** shell_cmd_descriptions = {
    "Shows this page",
    "Clears the screen",
    "Test command for the mouse driver"
};

void** shell_cmd_handlers = {
    shell_cmd_help,
    shell_cmd_clear,
    shell_cmd_mousetest
};

void shell_exec() {
    printf("> ");

    char* input[256];
    shell_get_string(input, 256);

    for (int i = 0; i < shell_cmds_len; i++) {

        if (!strcmp(input, shell_cmds[i])) {
            printf("YOUR COMMAND WORKY! %s\n", shell_cmds[i]);

            void(*handler)(int, char**);

            handler = shell_cmd_handlers[i];

            //if ((u64)shell_cmd_handlers[i] != NULL)
                handler(0, NULL); // This mister right here page faults. And i get page faults a lot
                                  // For example the shell_get_string void i have i would've put it in kb.c but i get a page fault when trying to run it.
                                  // Any clues anyone?
        }
    }

    /*if (!strcmp(input, "clear")) {
    }
    else if (!strcmp(input, "help")) {
    }
    else if (!strcmp(input, "mousetest")) {
    }
    else {
    }*/

    memset(input, 0, 256);
}

void shell_get_string(char* buf, size_t n) {
    size_t pos = 0;

    u8 c = 0;
    for (;;) {
        while (c == 0) {
            c = kb_get_char();
        }

        switch(c) {
            case '\n':
                printf("%s", "\n");
                return;

            case '\b':
                if (pos == 0)
                    break;
            
                printf("%c%s", c, " \b");

                buf[pos] = 0;
                pos--;
                break;

            default:
                if (pos >= n - 1)
                    break;

                printf("%c", c);

                buf[pos] = c;
                pos++;
                break;
        }

        c = 0;
    }
}