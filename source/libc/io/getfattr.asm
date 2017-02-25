include io.inc
include direct.inc
include winbase.inc

	.code

getfattr PROC USES ecx edx lpFilename:LPSTR

	.if GetFileAttributesA( lpFilename ) == -1

		.if GetFileAttributesW( __allocwpath( lpFilename ) ) == -1

			osmaperr()
		.endif
	.endif
	mov	esp,ebp
	ret

getfattr ENDP

	END

