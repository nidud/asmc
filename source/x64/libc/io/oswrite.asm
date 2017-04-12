include io.inc
include errno.inc
include winbase.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

oswrite PROC USES rbx h:SINT, b:PVOID, z:SIZE_T
local	lpNumberOfBytesWritten:SIZE_T

	mov	rbx,r8
	lea	rax,_osfhnd
	mov	rcx,[rax+rcx*8]
	.if	WriteFile( rcx, rdx, r8d, addr lpNumberOfBytesWritten, 0 )

		mov	rax,lpNumberOfBytesWritten
		.if	rax != rbx
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
