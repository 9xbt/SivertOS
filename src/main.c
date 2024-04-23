#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "limine.h"
#include "flanterm/flanterm.h"
#include "flanterm/backends/fb.h"

// Set the base revision to 1, this is recommended as this is the latest
// base revision described by the Limine boot protocol specification.
// See specification for further info.

static volatile LIMINE_BASE_REVISION(1);

// The Limine requests can be placed anywhere, but it is important that
// the compiler does not optimise them away, so, usually, they should
// be made volatile or equivalent, _and_ they should be accessed at least
// once.

static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

// Halt and catch fire function.
static void hcf(void) {
    asm ("cli");
    for (;;) {
        asm ("hlt");
    }
}

// The following will be our kernel's entry point.
// If renaming _start() to something else, make sure to change the
// linker script accordingly.
void _start(void) {
    // Ensure the bootloader actually understands our base revision (see spec).
    if (LIMINE_BASE_REVISION_SUPPORTED == false) {
        hcf();
    }

    // Ensure we got a framebuffer.
    if (framebuffer_request.response == NULL
     || framebuffer_request.response->framebuffer_count < 1) {
        hcf();
    }

    // Fetch the first framebuffer.
    struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];

    // Note: we assume the framebuffer model is RGB with 32-bit pixels.
    /*for (size_t i = 0; i < 100; i++) {
        volatile uint32_t *fb_ptr = framebuffer->address;
        fb_ptr[i * (framebuffer->pitch / 4) + i] = 0xffffff;
    }*/


    struct flanterm_context *ft_ctx = flanterm_fb_simple_init(
        framebuffer->address, framebuffer->width, framebuffer->height, framebuffer->pitch
    );

    const char msg[] = "Welcome to SivertOS!\n\nGoodbye, cruel world.\n";

    flanterm_write(ft_ctx, msg, sizeof(msg));

    // We're done, just hang...
    hcf();
}