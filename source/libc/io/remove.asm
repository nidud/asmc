include io.inc

	.code

remove	PROC file:LPSTR

	.if DeleteFile( file )

		mov	eax,1
		mov	_diskflag,eax
		dec	eax
	.else
		osmaperr()
	.endif
	ret

remove	ENDP

	END
