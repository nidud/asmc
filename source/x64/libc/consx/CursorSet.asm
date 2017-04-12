include consx.inc

	.code

CursorSet PROC USES rax cursor:PTR S_CURSOR
	mov	rax,cursor
	mov	eax,DWORD PTR [rax].S_CURSOR.x
	SetConsoleCursorPosition( hStdOutput, eax )
	SetConsoleCursorInfo( hStdOutput, cursor )
	ret
CursorSet ENDP

	END