
;--- v2.16: Similar to invoke43.asm, but this time without ADDR,
;--- just the offset operator. JWasm is to reject this, like Masm
;--- does ( argument type mismatch ).

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
	invoke proc2, offset var1	; is to be rejected (it wasn't before v2.16)
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
