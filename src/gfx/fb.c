#include <gfx/fb.h>
#include <lib/alloc.h>

fb_t* fb_create(u32 width, u32 height, u32* fb_address) {
    fb_t* fb = (fb_t*)kmalloc(sizeof(fb_t));
    fb->address = fb_address;
    fb->width = width;
    fb->height = height;
    fb->pitch = width * 4;

    return fb;
}

fb_t* fb_create_new(u32 width, u32 height) {
    fb_t* fb = (fb_t*)kmalloc(sizeof(fb_t));
    fb->address = (u32*)kmalloc(width * height * 4);
    fb->width = width;
    fb->height = height;
    fb->pitch = width * 4;

    return fb;
}

void fb_update_size(fb_t* fb, u32 width, u32 height) {
    kfree(fb->address);
    fb->address = (u32*)kmalloc(width * height * 4);
    fb->width = width;
    fb->height = height;
    fb->pitch = width * 4;
}

void fb_destroy(fb_t* fb) {
    kfree(fb->address);
    kfree(fb);
}