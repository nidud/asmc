
;--- v2.19: mz format and org in first segment.

	.286
	.model small
	.stack 1024

	.data

text1 db "xxxx",13,10,'$'

	.code

	org 80h

start:
	mov ax, @data
	mov ds, ax
	mov dx, offset text1
	mov ah,9
	int 21h
	mov ax, 4c00h
	int 21h

	end start
