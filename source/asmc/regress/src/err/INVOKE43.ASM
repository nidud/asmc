
;--- v2.16: ADDR is to truncate a 32-bit offset to 16-bit.
;--- a possible warning should NOT be emitted by INVOKE, but
;--- when the generated "pushw <offset32>" is translated.
;--- See also invoke41.asm, which is the "reverse" case.
;--- v2.19: now warning 'Magnitude of offset exceeds 16-bit' is displayed.

	.386
	.model small
	.stack 2048
	.dosseg

	.data

var1 db 0

_TEXT16 segment use16 public 'CODE'

proc2 proc stdcall p1:word
	ret
proc2 endp

proc1 proc far
	invoke proc2, addr var1	; offset is to be pushed as 16-bit 
	ret
proc1 endp

start:
	mov ax, @data
	mov ds, ax
	mov ax, 4c00h
	int 21h

_TEXT16 ends

	.code

	mov eax, offset var1
	ret

	end start
