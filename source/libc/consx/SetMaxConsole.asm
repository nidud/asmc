include consx.inc

	.code

SWPFLAG equ SWP_NOSIZE or SWP_NOACTIVATE or SWP_NOZORDER

SetMaxConsole PROC

	;
	; japheth 2014-01-10 - reposition to desktop position 0,0
	;
	SetWindowPos(GetConsoleWindow(),0,0,0,0,0,SWPFLAG)
	GetLargestConsoleWindowSize( hStdOutput )
	mov	edx,eax
	shr	edx,16
	movzx	eax,ax

	.if eax < 80 || edx < 16
		mov eax,80
		mov edx,25
	.elseif eax > 255 || edx > 255
		.if eax > 255
			mov eax,240
		.endif
		.if edx > 255
			mov edx,240
		.endif
	.endif

	SetConsoleSize( eax, edx )
	ret

SetMaxConsole ENDP

	END
