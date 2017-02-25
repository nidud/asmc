include io.inc
include errno.inc
include winbase.inc

	.code

oswrite PROC h:SINT, b:PVOID, z:SIZE_T
local	lpNumberOfBytesWritten
	mov	eax,h
	mov	edx,_osfhnd[eax*4]
	.if	WriteFile( edx, b, z, addr lpNumberOfBytesWritten, 0 )
		mov	eax,lpNumberOfBytesWritten
		.if	eax != z
			mov errno,ERROR_DISK_FULL
			xor eax,eax
		.endif
	.else
		call	osmaperr
		xor	eax,eax
	.endif
	ret
oswrite ENDP

	END
