#include <limine.h>
#include <flanterm/flanterm.h>
#include <flanterm/backends/fb.h>
#include <arch/x86_64/io.h>
#include <arch/x86_64/cpu/pic.h>
#include <arch/x86_64/cpu/serial.h>
#include <arch/x86_64/tables/gdt/gdt.h>
#include <arch/x86_64/tables/idt/idt.h>
#include <drivers/kb.h>
#include <drivers/mouse.h>
#include <mm/pmm.h>
#include <mm/vmm.h>
#include <mm/heap.h>
#include <lib/alloc.h>
#include <lib/panic.h>
#include <lib/printf.h>
#include <apps/shell.h>

LIMINE_BASE_REVISION(1)

volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

volatile struct limine_hhdm_request hhdm_request = {
    .id = LIMINE_HHDM_REQUEST,
    .revision = 0
};

struct limine_framebuffer *framebuffer = NULL;
struct flanterm_context *flanterm_context = NULL;

u32 *fb_addr;
u64  hhdm_offset;

void hcf() {
    for (;;)
        asm volatile ("hlt");
}

void putchar_(char c) {
    char msg[] = {c};
    flanterm_write(flanterm_context, msg, sizeof(msg));
}

int mubsan_log(const char* format, ...) {
    va_list args;
    va_start(args, format);
    const int ret = vprintf(format, args);
    va_end(args);

    return ret;
}

void _start(void) {
    // Ensure the bootloader actually understands our base revision (see spec).
    if (LIMINE_BASE_REVISION_SUPPORTED == false) {
        hcf();
    }

    // Ensure we got a framebuffer.
    if (framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count < 1) {
        hcf();
    }

    hhdm_offset = hhdm_request.response->offset;
    framebuffer = framebuffer_request.response->framebuffers[0];
    fb_addr = framebuffer->address;

    flanterm_context = flanterm_fb_simple_init(
        framebuffer->address, framebuffer->width, framebuffer->height, framebuffer->pitch
    );

    const char welcome_msg[] = "Welcome to \033[1;36mSivertOS\033[0m!\n\n";
    flanterm_write(flanterm_context, welcome_msg, sizeof(welcome_msg));

    gdt_init();
    serial_init();
    idt_init();
    pic_remap();
    kb_init();
    mouse_init();
    pmm_init();
    vmm_init();

    //ata_init

    kheap_init(PAGE_SIZE * 65536); /* 256mb */

    for (;;) {
        shell_exec();
    }

    /*for (;;) {
        asm ("hlt");
    }*/
}