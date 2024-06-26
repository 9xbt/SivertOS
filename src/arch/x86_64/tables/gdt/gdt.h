/*
 *  CREDITS: asterd-og on GitHub
 *  https://github.com/asterd-og/QuasarOS/
 */

#pragma once

#include <types.h>

typedef struct {
    u16 size;
    u64 offset;
} __attribute__((packed)) gdtr;

void gdt_init();

extern gdtr gdt_data;