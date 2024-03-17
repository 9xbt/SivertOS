; This file is part of SivertOS, the radioactive 16-bit assembly operating system
; https://github.com/9xbt/SivertOS

%ifndef VGA_ASM
%define VGA_ASM

vga_clear:
    mov ax, 3 ; video mode
    int 10h   ; set the video mode
    ret       ; retire from the function

vga_write:
    mov ah, 0xE ; function code = teletype output

    .loop:
        lodsb     ; load string byte
        or al, al ; check for string terminator
        jz .end   ; retire from the loop
        int 10h   ; print the character
        jmp .loop ; loop
    .end:
        ret ; retire from the function

%endif