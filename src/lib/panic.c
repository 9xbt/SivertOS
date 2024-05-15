#include <lib/panic.h>

void panic(const char *format, ...) {
    asm volatile ("cli");
    
    for (u64 y = 0; y < framebuffer->height; y++) {
        for (u64 x = 0; x < framebuffer->width; x++) { 
            fb_addr[y * framebuffer->width + x] = 0xAA;
        }
    }

    flanterm_write(flanterm_context, "\033[37;44m\033[H\033[2J\033[?25l", 21);
    printf("SivertOS 0.0.1\nKernel panic!\n\n");

    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    printf("\n\nPlease restart your computer.\n");

    for (;;) asm volatile ("hlt");
}