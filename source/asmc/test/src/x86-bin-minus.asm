
;--- expression label - constant - label,
;--- jwasm used 32-bit for label subtraction, but 64-bit for constant subtraction.
;--- since v2.19, 64-bit is used in both cases.

	.286
	.model tiny

	.code
@:
	mov si, offset Z2
Z1  equ ($ - @)           ; this worked
Z2  equ ($ - 2 - @)       ; this works since v2.19

start:
	inc word ptr [bp-128+Z2]
	mov ah,4ch
	int 21h
	END start
