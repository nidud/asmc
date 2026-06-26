
;--- an address argument for invoke didn't work in 64-bit
;--- for stdcall or c calling convention.

	.x64
	.model flat
	.dosseg		; v2.19: line added
	option casemap:none

	.data
	.stack 1024

text db 'Hello world!', 0

	.code

printf proc c fstr:ptr, args:vararg
	ret
printf endp

	invoke printf, addr text

_TEXT16 segment use16 public 'CODE'
start:
	mov ax,4c00h
	int 21h
_TEXT16 ends

	end start
