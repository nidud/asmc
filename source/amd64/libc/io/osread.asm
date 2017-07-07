include io.inc
include errno.inc
include winbase.inc

	.code

	option	win64:rsp nosave

osread	PROC h:SINT, b:PVOID, z:SIZE_T

	local	count:DWORD

	lea	rax,_osfhnd
	mov	rcx,[rax+rcx*8]
	ReadFile(rcx, rdx, r8d, &count, 0)
	test	eax,eax
	mov	ecx,eax
	mov	eax,count
	jz	error
toend:
	ret
error:
	call	osmaperr
	xor	eax,eax
	jmp	toend
osread	ENDP

	END
