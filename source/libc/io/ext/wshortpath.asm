include io.inc
include direct.inc
include string.inc

	.code

wshortpath PROC path:LPSTR, buffer:LPSTR
	.if	!GetShortPathName( path, buffer, _MAX_PATH )
		call	osmaperr
		xor	eax,eax
	.else
		mov	eax,buffer
	.endif
	ret
wshortpath ENDP

	END