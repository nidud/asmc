include consx.inc

	.code

rcpush	PROC lines:UINT

	mov	eax,_scrcol
	mov	ah,BYTE PTR lines
	shl	eax,16
	rcopen( eax, 0, 0, 0, 0 )
	ret

rcpush	ENDP

	END
