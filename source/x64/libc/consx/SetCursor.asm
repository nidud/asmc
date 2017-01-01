include consx.inc

	.code

SetCursor PROC USES rax cursor:PTR S_CURSOR
	mov	rax,cursor
	mov	eax,DWORD PTR [rax].S_CURSOR.x
	SetConsoleCursorPosition( hStdOutput, eax )
	SetConsoleCursorInfo( hStdOutput, cursor )
	ret
SetCursor ENDP

	END