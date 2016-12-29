include io.inc

	.code

_eof	PROC handle:SINT
	_lseeki64( handle, 0, SEEK_CUR )
	push	edx
	push	eax
	_lseeki64( handle, 0, SEEK_END )
	pop	ecx
	cmp	eax,ecx
	pop	eax
	jne	not_eof
	cmp	eax,edx
	jne	not_eof
	cmp	eax,-1
	je	toend
	mov	eax,1
	jmp	toend
not_eof:
	_lseeki64( handle, eax::ecx, SEEK_SET )
	xor	eax,eax
toend:
	ret
_eof	ENDP

	END
