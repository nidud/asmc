include io.inc

	.code

remove	PROC file:LPSTR

	.if DeleteFile( file )

		xor eax,eax
	.else
		osmaperr()
	.endif
	ret

remove	ENDP

	END
