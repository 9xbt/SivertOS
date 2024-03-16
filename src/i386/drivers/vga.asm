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

vga_clear:
    mov ax, 3 ; video mode
    int 10h   ; set the video mode
    ret       ; retire from the function

vga_write:
    mov ah, 0xE ; function code = teletype output

    .loop:
        lodsb     ; load string byte
        or al, al ; check for string terminator
        jz .end   ; retire from the loop
        int 10h   ; print the character
        jmp .loop ; loop
    .end:
        ret ; retire from the function