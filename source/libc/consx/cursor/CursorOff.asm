include consx.inc

	.code

CursorOff PROC
local	cu:CONSOLE_CURSOR_INFO

	mov cu.dwSize,CURSOR_NORMAL
	mov cu.bVisible,0
	push eax
	SetConsoleCursorInfo( hStdOutput, addr cu )
	pop  eax
	ret

CursorOff ENDP

	END
