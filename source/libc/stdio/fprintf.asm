include stdio.inc

	.code

fprintf PROC C,
	file:	LPFILE,
	format: LPSTR,
	argptr: VARARG

	_stbuf( file )
	push	eax
	_output( file, format, addr argptr )
	pop	edx
	push	eax
	_ftbuf( edx, file )
	pop	eax
	ret
fprintf ENDP

	END
