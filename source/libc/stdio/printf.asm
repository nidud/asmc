include stdio.inc

	.code

printf	PROC C,
	format: LPSTR,
	argptr: VARARG

	_stbuf( addr stdout )
	push	eax
	_output( addr stdout, format, addr argptr )
	pop	edx
	push	eax
	_ftbuf( edx, addr stdout )
	pop	eax
	ret
printf	ENDP

	END
