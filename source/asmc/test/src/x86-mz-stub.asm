
    option MZ:40h

_TEXT segment 'CODE'
start16:
	push cs
	pop ds
	mov dx,offset text
	mov ah,9
	int 21h
	mov ax,4c01h
	int 21h
text db "It's a PE image",13,10,'$'
_TEXT ends

STACK segment stack 'STACK'
	db 128 dup (?)
STACK ends
    end start16
