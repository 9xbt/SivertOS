#pragma once

#include <types.h>
#include <limine.h>

void vbe_init();

extern u32* vbe_addr;
extern u64 vbe_width;
extern u64 vbe_height;
extern u64 vbe_pitch;