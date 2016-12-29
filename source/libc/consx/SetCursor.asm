include consx.inc

	.code

SetCursor PROC USES eax Cursor:PTR S_CURSOR

	mov eax,Cursor
	mov eax,DWORD PTR [eax].S_CURSOR.x

	SetConsoleCursorPosition( hStdOutput, eax )
	SetConsoleCursorInfo( hStdOutput, Cursor )
	ret

SetCursor ENDP

	END