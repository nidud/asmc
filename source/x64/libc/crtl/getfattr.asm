include io.inc
include direct.inc
include winbase.inc

	.code

	option	win64:2

getfattr PROC file:LPSTR

	.ifd GetFileAttributesW( __allocwpath( rcx ) ) == -1

		osmaperr()
	.endif
	ret

getfattr ENDP

	END

