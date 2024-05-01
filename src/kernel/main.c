#include <types.h>
#include <limine.h>
#include <video/vbe.h>
#include <tools/logger.h>
#include <arch/x86_64/io.h>
#include <arch/x86_64/cpu/serial.h>
#include <arch/x86_64/tables/gdt/gdt.h>
#include <flanterm/flanterm.h>
#include <flanterm/backends/fb.h>

struct flanterm_context *flanterm_context;

void idle(void) {
    for (;;) {
        __asm__ ("hlt");
    }
}

void _start(void) {
    gdt_init();
    serial_init();
    vbe_init();

    flanterm_context = flanterm_fb_simple_init(
        vbe_addr, vbe_width, vbe_height, vbe_pitch
    );

    const char welcome_msg[] = "Welcome to \033[1;36mSivertOS\033[0m!\n\n";
    flanterm_write(flanterm_context, welcome_msg, sizeof(welcome_msg));

    idle();
}