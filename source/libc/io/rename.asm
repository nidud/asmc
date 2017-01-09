include io.inc

	.code

rename	PROC Oldname:LPSTR, Newname:LPSTR

	.if MoveFile( Oldname, Newname )

		mov	eax,1
		mov	_diskflag,eax
		dec	eax
	.else
		osmaperr()
	.endif
	ret
rename	ENDP

	END
