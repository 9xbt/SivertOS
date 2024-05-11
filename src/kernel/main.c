#include <limine.h>
#include <video/vbe.h>
#include <arch/x86_64/io.h>
#include <arch/x86_64/cpu/pic.h>
#include <arch/x86_64/cpu/serial.h>
#include <arch/x86_64/tables/gdt/gdt.h>
#include <arch/x86_64/tables/idt/idt.h>
#include <drivers/kb.h>
#include <drivers/mouse.h>
#include <mm/pmm.h>
#include <mm/vmm.h>
#include <flanterm/flanterm.h>
#include <flanterm/backends/fb.h>
#include <libc/panic.h>
#include <libc/printf.h>
#include <tools/shell.h>

volatile struct limine_hhdm_request hhdm_request = {
    .id = LIMINE_HHDM_REQUEST,
    .revision = 0
};

struct flanterm_context *flanterm_context;

u64 hhdm_offset = 0;

void _start(void) {
    hhdm_offset = hhdm_request.response->offset;

    gdt_init();
    vbe_init();

    flanterm_context = flanterm_fb_simple_init(
        vbe_addr, vbe_width, vbe_height, vbe_pitch
    );

    const char welcome_msg[] = "Welcome to \033[1;36mSivertOS\033[0m!\n\n";
    flanterm_write(flanterm_context, welcome_msg, sizeof(welcome_msg));

    serial_init();
    
    idt_init();
    pic_remap();

    kb_init();
    mouse_init();

    pmm_init();
    vmm_init();

    for (;;) {
        shell_exec();
    }

    /*for (;;) {
        asm ("hlt");
    }*/
}

void putchar_(char c) {
    char msg[] = {c, '\0'};
    flanterm_write(flanterm_context, msg, sizeof(msg));
}

int mubsan_log(const char* format, ...) {
    va_list args;
    va_start(args, format);
    const int ret = vprintf(format, args);
    va_end(args);

    return ret;
}