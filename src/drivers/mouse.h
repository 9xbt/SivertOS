#pragma once

#include <types.h>
#include <arch/x86_64/tables/idt/idt.h>
#include <arch/x86_64/io.h>
#include <arch/x86_64/cpu/serial.h>
#include <kernel/kernel.h>

typedef struct {
    u8  left;
    u8  middle;
    u8  right;
    i32 x;
    i32 y;
} mouse_state_t;

typedef struct {
    mouse_state_t last;
    mouse_state_t current;
} mouse_t;

extern mouse_t mouse_state;

extern u8  mouse_left_pressed;
extern u8  mouse_middle_pressed;
extern u8  mouse_right_pressed;
extern u8  mouse_last_left_pressed;
extern u8  mouse_last_middle_pressed;
extern u8  mouse_last_right_pressed;
extern i32 mouse_x;
extern i32 mouse_y;
extern i32 mouse_last_x;
extern i32 mouse_last_y;

void mouse_init();