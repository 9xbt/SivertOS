#pragma once

#include <types.h>
#include <lib/printf.h>
#include <kernel/kernel.h>
#include <flanterm/flanterm.h>

void panic(const char *format, ...);