#include <lib/panic.h>

void panic(const char *format, ...) {
    asm volatile ("cli");

    cv_clear(framebuffer->address, framebuffer->width, framebuffer->height, 0x0000AA);

    flanterm_write(flanterm_context, "\033[37;44m\033[H\033[2J\033[?25l", 21);
    printf("SivertOS 0.0.1\nKernel panic!\n\n");

    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    printf("\n\nPlease restart your computer to continue.\n");

    for (;;) asm volatile ("hlt");
}