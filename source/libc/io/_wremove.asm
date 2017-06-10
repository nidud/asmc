include io.inc
include winbase.inc

	.code

_wremove PROC file:LPWSTR

	.if DeleteFileW( file )

		xor eax,eax
	.else
		osmaperr()
	.endif
	ret

_wremove ENDP

	END
