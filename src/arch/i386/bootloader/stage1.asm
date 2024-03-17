[BITS 16]
[ORG 7C00h]

call vga_clear

mov ah, 2    ; command
mov al, 1    ; sectors to read
mov ch, 0    ; cylinder
mov cl, 2    ; sector
mov dh, 0    ; head
mov dl, 80h  ; drive
mov bx, 0    ; extended segment
mov es, bx   ; bx -> es
mov bx, 500h ; kernel offset
int 13h      ; load the sectors

jc .error

jmp 0:500h ; jump to the kernel

.error:
    mov si, generic_error
    call vga_write
    mov si, disk_error
    call vga_write

    jmp $ ; halt execution

generic_error: db "stage1 fatal error: ", 0x00
disk_error: db "disk access failiure", 0x0D, 0x0A, 0x00

%include "src/arch/i386/hw/vga.asm"

times 510-($-$$) db 0 ; fill the remaining space of the sector with zeroes
dw 0xAA55             ; boot signature