include io.inc

	.code

_access PROC file:LPSTR, amode

	.if getfattr( file ) != -1

		.if amode == 2 && eax & _A_RDONLY

			mov eax,-1
		.else
			xor eax,eax
		.endif
	.endif
	ret

_access ENDP

	END