[global sse_supported]

sse_supported:
    mov eax, 0x1
    cpuid
    test edx, 1<<25
    jz .noSSE

    mov eax, 1
    ret

    .noSSE:
        mov eax, 0
        ret