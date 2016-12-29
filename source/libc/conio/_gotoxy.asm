include conio.inc

	.code

_gotoxy PROC x, y
	mov	eax,y
	shl	eax,16
	mov	ax,WORD PTR x
	SetConsoleCursorPosition( hStdOutput, eax )
	ret
_gotoxy ENDP

	END
