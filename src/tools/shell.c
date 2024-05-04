#include <tools/shell.h>

char* shell_get_input();


void shell_exec() {
    printf("$ ");

    char* input[256];
    shell_get_string(input, 256);

    if (!strcmp(input, "clear")) {
        flanterm_write(flanterm_context, "\033[2J\033[H", 7);
    }
    if (!strcmp(input, "test")) {
        printf("Hello, world!\n");
    }

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