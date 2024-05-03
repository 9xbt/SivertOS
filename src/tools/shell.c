#include <tools/shell.h>

char* shell_get_input();

void shell_exec() {
    printf("$ ");
    char* input = shell_get_input();

    if (!strcmp(input, "clear")) {
        flanterm_write(flanterm_context, "\033[2J\033[H", 7);
    }

    kfree(input);
}

char* shell_get_input() {
    char* ret = kmalloc(256);
    u8 pos = 0;

    u8 c = 0;
    for (;;) {
        while (c == 0) {
            c = kb_get_char();
        }

        putchar_(c);
        switch(c) {
            case '\n':
                return ret;

            case '\b':
                printf(" \b");

                ret[pos] = 0;
                pos--;
                break;

            default:
                ret[pos] = c;
                pos++;
                break;
        }

        c = 0;
    }
}