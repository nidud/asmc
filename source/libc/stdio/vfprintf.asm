include stdio.inc

	.code

vfprintf PROC file:LPFILE, format:LPSTR, args:PVOID
	_stbuf( file )
	push	eax
	_output( file, format, args )
	pop	ecx
	push	eax
	_ftbuf( ecx, file )
	pop	eax
	ret
vfprintf ENDP

	END
