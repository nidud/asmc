include consx.inc

	.code

CursorGet PROC USES ebx cursor:PTR S_CURSOR

  local ci:CONSOLE_SCREEN_BUFFER_INFO

	mov ebx,cursor

	.if GetConsoleScreenBufferInfo( hStdOutput, addr ci )

		mov eax,ci.dwCursorPosition
		mov DWORD PTR [ebx].S_CURSOR.x,eax
	.endif

	GetConsoleCursorInfo( hStdOutput, ebx )
	mov eax,[ebx].S_CURSOR.bVisible
	ret

CursorGet ENDP

	END
