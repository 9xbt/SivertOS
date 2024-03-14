[BITS 16]
[ORG 0x7C00]

mov al, 0x40
mov ah, 2
mov ch, 0
mov cl, 2
mov dh, 0
mov dl, 0x80
mov bx, 0x500
mov es, bx
mov bx, 0
int 13h
jnc $
jmp 0x500:0

times 510 - ($ - $$) db 0
dw 0xAA55