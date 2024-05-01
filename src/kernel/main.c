#include <types.h>
#include <limine.h>
#include <arch/x86_64/tables/gdt/gdt.h>
#include <video/vbe.h>
#include <flanterm/flanterm.h>
#include <flanterm/backends/fb.h>

static volatile LIMINE_BASE_REVISION(1);

static void hcf(void) {
    asm ("cli");
    for (;;) {
        asm ("hlt");
    }
}

void _start(void) {
    gdt_init();
    vbe_init();

    struct flanterm_context *ft_ctx = flanterm_fb_simple_init(
        vbe_addr, vbe_width, vbe_height, vbe_pitch
    );

    const char msg[] = "Welcome to \033[1;36mSivertOS\033[0m!";
    flanterm_write(ft_ctx, msg, sizeof(msg));

    hcf();
}