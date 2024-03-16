; This file is part of SivertOS, the radioactive 16-bit assembly operating system
; https://github.com/9xbt/SivertOS

[BITS 16]
[ORG 900h]

call vga_clear

mov si, str_1
call vga_write

; TODO: disable NMIs, enable A20, and load the GDT

jmp $

%include "src/i386/drivers/vga.asm"

str_1: db "Let's switch into protected mode!", 0