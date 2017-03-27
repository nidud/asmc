include stdio.inc

	.code

fwprintf proc c uses esi file:LPFILE, format:LPWSTR, argptr:VARARG

	mov  esi,_stbuf(file)
	xchg esi,_woutput(file, format, addr argptr)

	_ftbuf(eax, file)
	mov eax,esi
	ret

fwprintf ENDP

	END
