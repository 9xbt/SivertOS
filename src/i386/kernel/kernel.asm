; This file is part of SivertOS, the radioactive 16-bit assembly operating system
; https://github.com/9xbt/SivertOS

[BITS 16]
[ORG 900h]

mov ax, 0     ; move zero to ax
mov ds, ax    ; set the data segment to ax
mov es, ax    ; set the extended segment to ax
mov ss, ax    ; set the stack segment to ax
mov sp, 900h  ; set the stack pointer address

; TODO: disable NMIs, enable A20, and load the GDT

call disable_nmi

mov si, nmi_msg
call vga_write

call enable_a20

jmp $

%include "src/i386/hw/vga.asm"
%include "src/i386/hw/pm.asm"

nmi_msg: db "Disabled NMIs!", 0x0D, 0x0A, 0x00