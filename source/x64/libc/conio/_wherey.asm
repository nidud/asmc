include conio.inc

	.code

_wherey PROC
local	ci:CONSOLE_SCREEN_BUFFER_INFO

	.if GetConsoleScreenBufferInfo( hStdOutput, addr ci )

		movzx eax,ci.dwCursorPosition.y
	.endif
	ret
_wherey ENDP

	END
