
;--- v2.16: ADDR is to extend a 16-bit offset to 32-bit.

	.286
	.model small
	.stack 2048
	.dosseg
	.386

	.data

var1 db 0

_TEXT32 segment use32 public 'CODE'

proc2 proc stdcall p1:ptr
	ret
proc2 endp

proc1 proc far
	invoke proc2, addr var1	;offset is to be pushed as 32-bit 
	ret
proc1 endp

_TEXT32 ends

	.code
start:
	mov ax, @data
	mov ds, ax
	mov ax, offset var1
	mov ax, 4c00h
	int 21h

	end start
