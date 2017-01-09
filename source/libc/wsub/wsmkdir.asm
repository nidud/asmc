include direct.inc
include wsub.inc

	.code

wsmkdir PROC path:LPSTR

	.if	_mkdir( path )
		ermkdir( path )
	.else
		inc eax
	.endif
	ret

wsmkdir ENDP

	END
