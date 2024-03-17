[BITS 16]
[ORG 500h]

in al, 0x70
or al, 0x80
out 0x70, al
in al, 0x92
or al, 2
out 0x92, al
cli
lgdt [gdt]
mov eax, cr0
or eax, 1
mov cr0, eax

jmp $

%include "src/arch/i386/tables/gdt.asm"