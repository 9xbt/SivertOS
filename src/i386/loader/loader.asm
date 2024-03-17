; This file is part of SivertOS, the radioactive 16-bit assembly operating system
; https://github.com/9xbt/SivertOS

[BITS 16]
[ORG 7C00h]

call vga_clear      ; clear the screen
mov si, loading_msg ; loading message pointer -> si
call vga_write      ; print the message

mov ah, 2    ; command
mov al, 1    ; sectors to read
mov ch, 0    ; cylinder
mov cl, 2    ; sector
mov dh, 0    ; head
mov dl, 80h  ; drive
mov bx, 0    ; extended segment
mov es, bx   ; bx -> es
mov bx, 900h ; kernel offset
int 13h      ; load the sectors

jc .error

mov si, success_msg
call vga_write

jmp 0:900h ; jump to the kernel

.error:
    mov si, failiure_msg ; failiure message pointer -> si
    call vga_write       ; print the message

    jmp $ ; halt execution

loading_msg: db "Loading SivertOS... ", 0x00
success_msg: db "SUCCESS!", 0x0D, 0x0A, 0x00
failiure_msg: db "FAILED", 0x0D, 0x0A, 0x00

%include "src/i386/hw/vga.asm"

times 510-($-$$) db 0 ; fill the remaining space of the sector with zeroes
dw 0xAA55             ; boot signature