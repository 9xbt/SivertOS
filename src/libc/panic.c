#include <libc/panic.h>

void panic(const char *format, ...) {
    printf("\npanic(): Kernel panic! ");

    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    printf(".\n");
}