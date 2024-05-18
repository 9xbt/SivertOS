#include <ui/wm.h>
#include <gfx/fb.h>
#include <gfx/canvas.h>
#include <drivers/kb.h>
#include <drivers/mouse.h>
#include <kernel/kernel.h>

fb_t* back_fb;
fb_t* front_fb;

void wm_init() {
    back_fb = fb_create_new(framebuffer->width, framebuffer->height);
    front_fb = fb_create(framebuffer->width, framebuffer->height, framebuffer->address);
    cv_clear(back_fb->address, back_fb->width, back_fb->height, 0x000000);
}

void wm_update() {
    
}