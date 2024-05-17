#include <limine.h>
#include <flanterm/flanterm.h>
#include <flanterm/backends/fb.h>
#include <arch/x86_64/io.h>
#include <arch/x86_64/cpu/pic.h>
#include <arch/x86_64/cpu/sse.h>
#include <arch/x86_64/cpu/serial.h>
#include <arch/x86_64/tables/gdt/gdt.h>
#include <arch/x86_64/tables/idt/idt.h>
#include <drivers/kb.h>
#include <drivers/ata.h>
#include <drivers/mouse.h>
#include <mm/pmm.h>
#include <mm/vmm.h>
#include <mm/heap.h>
#include <fs/vfs.h>
#include <fs/ext2.h>
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

    u32 fg = 0x1b1c1b;
    u32 bg = 0xffffff;

    flanterm_context = flanterm_fb_init(
        NULL,
        NULL,
        framebuffer->address, framebuffer->width,
        framebuffer->height, framebuffer->pitch,
        framebuffer->red_mask_size, framebuffer->red_mask_shift,
        framebuffer->green_mask_size, framebuffer->green_mask_shift,
        framebuffer->blue_mask_size, framebuffer->blue_mask_shift,
        NULL,
        NULL, NULL,
        &fg, &bg,
        NULL, NULL,
        NULL, 0, 0, 1,
        0, 0,
        8
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
    kheap_init();
    sse_enable();
    ata_init();
    ext2_init();
    vfs_init();

    int i = 0;
    vfs_direntry* node = 0;

    while ((node = vfs_readdir(vfs_root, i)) != NULL) {
        printf("Found node: ");
        vfs_node* file = vfs_finddir(vfs_root, node->name);
        if (file->type == VFS_DIRECTORY)
            printf("\033[38;2;0;255;0m%s\033[0m\n", file->name);
        else {
            printf("%s\n", file->name);
            printf(" contents: ");
            char buf[1024];
            vfs_read(file, buf, 1024);
            printf("%s\n", buf);
        }
        i++;
    }

    for (;;) {
        shell_exec();
    }

    /*for (;;) {
        asm ("hlt");
    }*/
}