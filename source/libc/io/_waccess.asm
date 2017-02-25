include io.inc

	.code

_waccess proc file:LPWSTR, amode:SINT

	.if _wgetfattr( file ) != -1

		.if amode == 2 && eax & _A_RDONLY

			mov eax,-1
		.else
			xor eax,eax
		.endif
	.endif
	ret

_waccess endp

	END