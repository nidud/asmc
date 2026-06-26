
;--- v2.17: better check for scaling factor implemented

	.386
	.model flat

	.code

start:
	mov ax, 4C00h
	int 21
	mov ax,[ebx+edi*257]

    END start


