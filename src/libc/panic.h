#pragma once

#include <types.h>
#include <video/vbe.h>
#include <libc/printf.h>
#include <kernel/kernel.h>
#include <flanterm/flanterm.h>

void panic(const char *format, ...);