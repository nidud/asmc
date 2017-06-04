include io.inc

	.code

readword PROC file:LPSTR
  local result
	.if	osopen( file, 0, M_RDONLY, A_OPEN ) == -1
		xor	eax,eax
	.else
		push	eax
		mov	ecx,eax
		osread( ecx, addr result, 4 )
		pop	ecx
		push	eax
		_close( ecx )
		pop	eax
		.if	eax > 1
			mov	eax,result
		.else
			xor	eax,eax
		.endif
	.endif
	ret
readword ENDP

	END
