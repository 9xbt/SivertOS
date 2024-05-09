#include <libc/panic.h>

void panic(const char *format, ...) {
    asm volatile ("cli");
    
    for (int y = 0; y < vbe_height; y++) {
        for (int x = 0; x < vbe_width; x++) { 
            vbe_addr[y * vbe_width + x] = 0xAA;
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