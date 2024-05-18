#pragma once

#include <types.h>
#include <lib/libc.h>
#include <lib/printf.h>
#include <arch/x86_64/io.h>
#include <arch/x86_64/cpu/serial.h>
#include <arch/x86_64/tables/idt/idt.h>
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

void mouse_init();