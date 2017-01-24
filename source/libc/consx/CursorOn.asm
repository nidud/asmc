include consx.inc

	.code

CursorOn PROC USES eax
local	cu:CONSOLE_CURSOR_INFO

	mov cu.dwSize,CURSOR_NORMAL
	mov cu.bVisible,1

	SetConsoleCursorInfo( hStdOutput, addr cu )
	ret

CursorOn ENDP

	END
