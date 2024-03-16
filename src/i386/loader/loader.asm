; This file is part of SivertOS, the radioactive 16-bit assembly operating system
; https://github.com/9xbt/SivertOS

[BITS 16]
[ORG 7C00h]

mov ah, 2    ; command
mov al, 1    ; sectors to read
mov ch, 0    ; cylinder
mov cl, 2    ; sector
mov dh, 0    ; head
mov dl, 80h  ; drive
mov bx, 0    ;
mov es, bx   ;
mov bx, 900h ; kernel offset
int 13h      ; load the sectors

mov al, ah
add al, 65
mov ah, 0xE
int 10h

jc $ ; halt if an error occurs

;mov ax, 0     ; move zero to ax
;mov ds, ax    ; set the data segment to ax
;mov es, ax    ; set the extended segment to ax
;mov ss, ax    ; set the stack segment to ax
;mov sp, 500h  ; set the stack pointer address

;in al, 0x92
;or al, 2
;out 0x92, al

jmp 0:900h ; start the kernel

times 510-($-$$) db 0 ; fill the remaining space of the sector with zeroes
dw 0xAA55             ; boot signature