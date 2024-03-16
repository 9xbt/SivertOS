; This file is part of SivertOS, the radioactive 16-bit assembly operating system
; https://github.com/9xbt/SivertOS

[BITS 16]
[ORG 900h]

call vga_clear

mov si, test_string
call vga_write

jmp $

%include "src/i386/drivers/vga.asm"

test_string: db "Hello, world!", 0