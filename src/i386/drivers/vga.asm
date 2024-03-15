[BITS 16]

vga_clear:
    mov ax, 3 ; video mode
    int 10h   ; set the video mode
    ret       ; retire from the function

vga_write:
    .loop:
        lodsb     ; load string byte
        or al, al ; check if al is null
        jz .end   ; return if null

        mov al, 'A'
        mov ah, 0xE ; function code = teletype output
        int 10h     ; print the character

        jmp vga_write ; loop
    .end:
        ret ; retire from the function