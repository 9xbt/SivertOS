#pragma once

#include <types.h>
#include <arch/x86_64/tables/idt/idt.h>
#include <arch/x86_64/io.h>
#include <arch/x86_64/cpu/serial.h>
#include <video/vbe.h>

extern u8  mouse_left_pressed;
extern u8  mouse_middle_pressed;
extern u8  mouse_right_pressed;
extern i32 mouse_x;
extern i32 mouse_y;
extern i32 mouse_last_x;
extern i32 mouse_last_y;

void mouse_init();