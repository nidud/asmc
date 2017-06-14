include conio.inc

	.code

	OPTION WIN64:2, STACKBASE:rsp

_gotoxy PROC x, y
	mov	eax,edx
	shl	eax,16
	mov	ax,cx
	SetConsoleCursorPosition( hStdOutput, eax )
	ret
_gotoxy ENDP

	END
