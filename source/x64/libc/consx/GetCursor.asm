include consx.inc

	.code

GetCursor PROC USES rbx cursor:PTR S_CURSOR
local	ci:CONSOLE_SCREEN_BUFFER_INFO
	mov	rbx,rcx
	.if	GetConsoleScreenBufferInfo( hStdOutput, addr ci )
		mov eax,ci.dwCursorPosition
		mov DWORD PTR [rbx].S_CURSOR.x,eax
	.endif
	GetConsoleCursorInfo( hStdOutput, rbx )
	mov	eax,[rbx].S_CURSOR.bVisible
	ret
GetCursor ENDP

	END
