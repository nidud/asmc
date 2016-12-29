include consx.inc

	.data

asciisymbol	label qword
ASCII_DOT	db 7
ASCII_RIGHT	db 16
ASCII_LEFT	db 17
ASCII_UP	db 0x1E
ASCII_DOWN	db 0x1F
ASCII_ARROWD	db 25
ASCII_RADIO	db 7
		db 0
ascii		db 7,16,17,1Eh,1Fh,25,7,0
ttf		db 0CFh,'<','>',0CFh,9Eh,0CFh,'*',0

	.code

setasymbol PROC
	lea	ecx,ttf
	.if	console & CON_ASCII
		lea	ecx,ascii
	.endif
	mov	eax,[ecx]
	mov	DWORD PTR asciisymbol,eax
	mov	eax,[ecx+4]
	mov	DWORD PTR asciisymbol[4],eax
	ret
setasymbol ENDP

	END
