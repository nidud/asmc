include io.inc
include winbase.inc

	.code

remove	PROC file:LPSTR

	.if DeleteFileA( file )

		xor eax,eax
ifdef __DZ__
		mov _diskflag,1
endif
	.else
		osmaperr()
	.endif
	ret

remove	ENDP

	END
