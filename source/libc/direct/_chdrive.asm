include errno.inc
include winbase.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

_chdrive PROC drive:SINT
	mov	eax,[esp+4]
	cmp	eax,1
	jl	error1
	cmp	eax,31
	ja	error1
	add	al,'A' - 1
	mov	ah,':'
	push	eax
	mov	eax,esp
	SetCurrentDirectory( eax )
	pop	ecx
	test	eax,eax
	jz	error2
	xor	eax,eax
toend:
	ret
error1:
	mov	errno,EACCES
	mov	oserrno,ERROR_INVALID_DRIVE
	or	eax,-1
	jmp	toend
error2:
	call	osmaperr
	jmp	toend
_chdrive ENDP

	END
