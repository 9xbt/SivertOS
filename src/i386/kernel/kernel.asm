; SivertOS - The radioactive 16-bit assembly operating system 
; Copyright © 2024 Mobren
;
; This program is free software; you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation; either version 2 of the License, or (at
; your option) any later version.
;
; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
;
; You should have received a copy of the GNU General Public License along
; with this program; if not, write to the Free Software Foundation, Inc.,
; 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

[BITS 16]
[ORG 900h]

jmp _start

%include "src/i386/drivers/vga.asm"

_start:
    ;call vga_clear

    mov al, 'A'
    mov ah, 0xE
    int 10h

    mov si, test_string
    call vga_write

    jmp $

test_string: db "Hello, world!", 0