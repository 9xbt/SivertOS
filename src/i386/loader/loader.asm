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
[ORG 7C00h]

mov ah, 2    ; command
mov al, 1    ; sectors to read
mov ch, 0    ; cylinder
mov cl, 2    ; sector
mov dh, 0    ; head
mov dl, 80h  ; drive
mov bx, 0    ;
mov es, bx   ;
mov bx, 900h ; kernel offset
int 13h      ; load the sectors

mov al, ah
add al, 65
mov ah, 0xE
int 10h

jc $ ; halt if an error occurs

mov ax, 0     ; move zero to ax
mov ds, ax    ; set the data segment to ax
mov es, ax    ; set the extended segment to ax
mov ss, ax    ; set the stack segment to ax
mov sp, 500h  ; set the stack pointer address

jmp 0:900h ; start the kernel

times 510-($-$$) db 0 ; fill the remaining space of the sector with zeroes
dw 0xAA55             ; boot signature