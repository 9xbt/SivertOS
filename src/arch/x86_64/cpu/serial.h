/*
 *  CREDITS: asterd-og on GitHub
 *  https://github.com/asterd-og/QuasarOS/
 */

#pragma once

#include <types.h>

#define COM1 0x3F8

int serial_init();
void serial_send(char* pStr);
void serial_printf(char *fmt, ...);