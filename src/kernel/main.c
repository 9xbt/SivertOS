#include <types.h>
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
#include <heap/heap.h>
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

void kernel_idle(void) {
    for (;;) {
        __asm__ ("hlt");
    }
}

void _start(void) {
    gdt_init();
    serial_init();
    vbe_init();
    
    __asm__ ("cli");
    idt_init();
    pic_remap();
    __asm__ ("sti");

    kb_init();
    mouse_init();

    pmm_init();
    vmm_init();

    flanterm_context = flanterm_fb_simple_init(
        vbe_addr, vbe_width, vbe_height, vbe_pitch
    );

    const char welcome_msg[] = "Welcome to \033[1;36mSivertOS\033[0m!\n\n";
    flanterm_write(flanterm_context, welcome_msg, sizeof(welcome_msg));

    for (;;) {
        shell_exec();
    }

    kernel_idle();
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

u64 __stack_chk_guard = 1234567890; // This is meant be generated at runtime with a random number generator, but having it like this works just fine

void __stack_chk_fail() {
    panic("__stack_chk_fail(): something went wery wrong with the stack");
}