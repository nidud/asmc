include consx.inc

	.code

CursorOff PROC
local	cu:CONSOLE_CURSOR_INFO
	mov	cu.dwSize,CURSOR_NORMAL
	mov	cu.bVisible,0
	SetConsoleCursorInfo( hStdOutput, addr cu )
	ret
CursorOff ENDP

	END
