[BITS 16]
[ORG 900h]

jmp _start

%include "src/i386/drivers/vga.asm"

_start:
    ;call vga_clear

    mov al, 'A'
    mov ah, 0xE
    int 10h

    mov si, test_string
    call vga_write

    jmp $

test_string: db "Hello, world!", 0