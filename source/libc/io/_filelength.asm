include io.inc

	.code

_filelength PROC handle:SINT
	push	eax
	mov	edx,esp
	mov	eax,handle
	mov	eax,_osfhnd[eax*4]
	GetFileSize( eax, edx )
	pop	edx
	ret
_filelength ENDP

	END
