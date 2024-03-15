[BITS 16]
[ORG 7C00h]

mov ah, 2    ; command
mov al, 40h  ; sectors to read (64)
mov ch, 0    ; cylinder
mov cl, 2    ; sector
mov dh, 0    ; head
mov dl, 80h  ; drive
mov bx, 500h ; address 
mov es, bx   ; move the address into the extra segment register
int 13h      ; load the sectors

jnc $      ; halt if an error occurs
jmp 500h:0 ; start the kernel

times 510-($-$$) db 0 ; fill the remaining space of the sector with zeroes
dw 0xAA55             ; boot signature