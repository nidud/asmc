include io.inc
include errno.inc
include winbase.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

osread	PROC h:SINT, b:PVOID, z:SIZE_T

	local	count:QWORD

	lea	rax,_osfhnd
	mov	rcx,[rax+rcx*8]
	ReadFile( rcx, rdx, r8d, addr count, 0 )
	test	rax,rax
	mov	rcx,rax
	mov	rax,count
	jz	error
toend:
	ret
error:
	call	osmaperr
	xor	rax,rax
	jmp	toend
osread	ENDP

	END
