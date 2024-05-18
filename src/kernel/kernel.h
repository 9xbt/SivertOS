#pragma once

#include <types.h>
#include <limine.h>
#include <gfx/fb.h>

extern volatile struct limine_framebuffer_request framebuffer_request;
extern volatile struct limine_hhdm_request hhdm_request;
extern struct limine_framebuffer *framebuffer;
extern struct flanterm_context *flanterm_context;

extern u64   hhdm_offset;
extern fb_t* back_fb;
extern fb_t* front_fb;

extern struct flanterm_context *flanterm_context;