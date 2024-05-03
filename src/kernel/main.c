#include <types.h>
#include <limine.h>
#include <video/vbe.h>
#include <tools/logger.h>
#include <arch/x86_64/io.h>
#include <arch/x86_64/cpu/pic.h>
#include <arch/x86_64/cpu/serial.h>
#include <arch/x86_64/tables/gdt/gdt.h>
#include <arch/x86_64/tables/idt/idt.h>
#include <drivers/kb.h>
#include <flanterm/flanterm.h>
#include <flanterm/backends/fb.h>
#include <libc/printf.h>

struct flanterm_context *flanterm_context;

void kernel_idle(void) {
    for (;;) {
        __asm__ ("hlt");
    }
}

void _start(void) {
    gdt_init();
    serial_init();

    __asm__ ("cli");
    idt_init();
    pic_remap();
    __asm__ ("sti");

    kb_init();
    vbe_init();

    flanterm_context = flanterm_fb_simple_init(
        vbe_addr, vbe_width, vbe_height, vbe_pitch
    );

    const char welcome_msg[] = "Welcome to \033[1;36mSivertOS\033[0m!\n\n";
    flanterm_write(flanterm_context, welcome_msg, sizeof(welcome_msg));

    printf("No freezie before read key mate\n");

    __asm__ ("int $33");

    printf("Interrupt pass?\n");

    printf("No freezie mate\n");

    u8 c = 0;
    for (;;) {
        while (c == 0) {
            c = kb_get_char();
        }

        putchar_(c);
        c = 0;
    }
    
    for (;;) {
        __asm__ ("hlt");
    }
}

void putchar_(char c) {
    char msg[] = {c, '\0'};
    flanterm_write(flanterm_context, msg, sizeof(msg));
}

int mubsan_log(const char* format, ...) {
    printf("Test");

    va_list args;
    va_start(args, format);
    const int ret = vprintf(format, args);
    va_end(args);

    return ret;
}