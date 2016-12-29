include io.inc

	.code

rename	PROC Oldname:LPSTR, Newname:LPSTR

	.if MoveFile( Oldname, Newname )

		xor eax,eax
	.else
		osmaperr()
	.endif
	ret
rename	ENDP

	END
