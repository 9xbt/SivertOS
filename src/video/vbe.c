#include <video/vbe.h>

static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

u32* vbe_addr;
u64 vbe_width;
u64 vbe_height;
u64 vbe_pitch;

void vbe_init() {
    struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];
    vbe_addr = framebuffer->address;
    vbe_width = framebuffer->width;
    vbe_height = framebuffer->height;
    vbe_pitch = framebuffer->pitch;
}