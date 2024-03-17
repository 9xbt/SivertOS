; This file is part of SivertOS, the radioactive 16-bit assembly operating system
; https://github.com/9xbt/SivertOS

%ifndef PM_ASM
%define PM_ASM

enable_nmi:
    in al, 0x70  ; inb(0x70)
    and al, 0x80 ; al & 0x7F
    out 0x70, al ; outb(0x70, al)
    ret          ; retire from the function

disable_nmi:
    in al, 0x70  ; inb(0x70)
    or al, 0x80  ; al | 0x80
    out 0x70, al ; outb(0x70, al)
    ret          ; retire from the function

enable_a20:
    in al, 0x92  ; inb(0x92)
    or al, 2     ; al | 2
    out 0x92, al ; outb(0x92, al)
    ret          ; retire from the function

%endif