include consx.inc

	.code

SetConsoleSize PROC cols, rows

	local	bz:COORD
	local	rc:SMALL_RECT
	local	ci:CONSOLE_SCREEN_BUFFER_INFO

	.if	GetConsoleScreenBufferInfo( hStdOutput, addr ci )

		mov	rc.Left,0
		mov	rc.Top,0
		mov	eax,cols
		mov	bz.x,ax
		dec	eax
		mov	rc.Right,ax
		mov	edx,rows
		mov	bz.y,dx
		dec	edx
		mov	rc.Bottom,dx

		SetConsoleWindowInfo( hStdOutput, 1, addr rc )
		SetConsoleScreenBufferSize( hStdOutput, bz )
		SetConsoleWindowInfo( hStdOutput, 1, addr rc )

		.if	GetConsoleScreenBufferInfo( hStdOutput, addr ci )
			mov	eax,ci.dwSize
			movzx	edx,ax
			mov	_scrcol,edx
			shr	eax,16
			dec	eax
			mov	_scrrow,eax
		.endif
	.endif
	ret

SetConsoleSize ENDP

	END
