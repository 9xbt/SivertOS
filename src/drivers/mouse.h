#pragma once

#include <types.h>
#include <arch/x86_64/tables/idt/idt.h>
#include <arch/x86_64/io.h>

extern u8  mouse_left_pressed;
extern u8  mouse_middle_pressed;
extern u8  mouse_right_pressed;
extern u32 mouse_x;
extern u32 mouse_y;

void mouse_init();