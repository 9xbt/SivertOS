gdt:
    dw .size - 1
    dd .start

    .start:
        ; null segment
        dw 0x0000    ; Limit
        dw 0x0000    ; Base (low 16 bits)
        db 0x00      ; Base (mid 8 bits)
        db 00000000b ; Access
        db 00000000b ; Granularity
        db 0x00      ; Base (high 8 bits)

        ; code segment
        dw 0xFFFF    ; Limit
        dw 0x0000    ; Base (low 16 bits)
        db 0x00      ; Base (mid 8 bits)
        db 10011011b ; Access
        db 11001111b ; Granularity
        db 0x00      ; Base (high 8 bits)

        ; data segment
        dw 0xFFFF    ; Limit
        dw 0x0000    ; Base (low 16 bits)
        db 0x00      ; Base (mid 8 bits)
        db 10010011b ; Access
        db 11001111b ; Granularity
        db 0x00      ; Base (high 8 bits)

    .end:

    .size: equ .end - .start