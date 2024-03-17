[BITS 16]
[ORG 7C00h]

mov ax, 0x03
int 10h

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

jc $

jmp 0:500h ; jump to the kernel

times 510-($-$$) db 0 ; fill the remaining space of the sector with zeroes
dw 0xAA55             ; boot signature