include io.inc
include direct.inc
include winbase.inc

	.code

_wgetfattr PROC USES ecx edx lpFilename:LPWSTR

	.if GetFileAttributesW( lpFilename ) == -1

		osmaperr()
	.endif
	ret

_wgetfattr ENDP

	END

