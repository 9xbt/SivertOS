#pragma once

#include <types.h>
#include <kernel/kernel.h>
#include <arch/x86_64/cpu/serial.h>
#include <flanterm/flanterm.h>

void logger_info(char* buf, usize count);
void logger_success(char* buf, usize count);
void logger_warn(char* buf, usize count);
void logger_error(char* buf, usize count);