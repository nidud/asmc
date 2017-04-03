include stdio.inc

	.code

wprintf proc c uses esi format:LPWSTR, argptr:VARARG

	mov  esi,_stbuf( addr stdout )
	xchg esi,_woutput( addr stdout, format, addr argptr )
	mov  edx,eax

	_ftbuf( edx, addr stdout )
	mov eax,esi
	ret

wprintf endp

	END
