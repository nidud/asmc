include stdio.inc

	.code

wprintf proc c format:LPWSTR, argptr:VARARG
	_stbuf( addr stdout )
	push	eax
	_woutput( addr stdout, format, addr argptr )
	pop	edx
	push	eax
	_ftbuf( edx, addr stdout )
	pop	eax
	ret
wprintf endp

	END
