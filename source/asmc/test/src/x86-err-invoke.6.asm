
;--- similar to invoke41.asm, this time with "offset" instead of "addr".
;--- Masm rejects the argument ("argument type mismatch").
;--- jwasm accepted it up to v2.15, pushed it as a word only, though.

	.286
	.model small
	.stack 2048
	.dosseg
	.386

	.data

var1 db 0

	.code

start:
	mov ax,@data
	mov ds,ax
	mov ax,offset var1
	mov ax,4c00h
	int 21h

_TEXT32 segment use32 public 'CODE'

proc1 proc stdcall p1:ptr
	ret
proc1 endp

proc2 proc
	invoke proc1, offset var1
	ret
proc2 endp

_TEXT32 ends

	end start
