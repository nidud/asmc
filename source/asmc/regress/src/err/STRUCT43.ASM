
;--- v2.19: error msg ( "symbol not defined" ) was omitted.

	.model small
	.stack 1000h

S1 struct
v1  dw ?
v2  dw ?
v3  db 32 - v3 dup (?)
S1 ends

	.code
start:
	mov ah, 4Ch
	int 21h

	end start
