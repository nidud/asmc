include crtl.inc
include io.inc

	.code

setfattr PROC lpFilename:LPTSTR, Attributes:UINT

	.if	!SetFileAttributes( lpFilename, Attributes )

		osmaperr()
	.else

		xor eax,eax
		mov byte ptr _diskflag,2
	.endif
	ret
setfattr ENDP

	END
