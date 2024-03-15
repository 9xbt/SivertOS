[BITS 16]
[ORG 0x500]

call vga_clear

mov si, test_string
call vga_write

mov al, 'B'
mov ah, 0xE
int 10h

jmp $

test_string: db "Hello, world!", 0

%include "src/i386/drivers/vga.asm"