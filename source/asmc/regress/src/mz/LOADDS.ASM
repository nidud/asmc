
;--- v2.15: <loadds> parameter was ignored if proc had no params and locals

	.286
	.model small
	.stack 1024

	.code

p1 proc far pascal <loadds>
	mov ax,1234h
	ret
p1 endp

p2 proc far pascal <loadds>
	mov ax,4321h
	ret
p2 endp

start:
	mov ax,4c00h
	int 21h

	END start

