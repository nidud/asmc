include crtl.inc
include io.inc

	.code

setfattr PROC lpFilename:LPTSTR, Attributes:UINT

	.if !SetFileAttributes( lpFilename, Attributes )

		osmaperr()
	.else
		xor eax,eax
	.endif
	ret
setfattr ENDP

	END
