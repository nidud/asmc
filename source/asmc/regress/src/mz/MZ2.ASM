
;--- mz without .dosseg; .const behind .stack and data?
;--- didn't work with v2.12

	.286
	.MODEL SMALL
	option casemap:none

?DISP equ 1

	.stack 80h

	.data

v1	db -1,-2,-3,-4

	.data?

buffer db 16 dup (?)

	.code

start:
	mov ax,@data
	mov ds,ax
if ?DISP
	mov dx,offset strng
	mov ah,9
	int 21h
endif
	mov bx,offset v1
	mov cx,offset v2
	mov ah,4Ch
	int 21h

	.const 
if ?DISP
strng db "string in .const",13,10,'$'
endif
v2	db 1,2,3,4

	END start
