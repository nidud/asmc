
;--- v2.16: warning level 3 "magnitude of offset exceeds 16-bit"
;--- before v2.16, it was an error.

	.286
	.model small
	.stack 2048

	.code
	mov ax,es:[0DEADBEEFh]  ; es = assume nothing
	mov ax,ds:[0DEADBEEFh]  ; ds = assume dgroup
start:
	mov ax,4c00h
	int 21h

	END start

