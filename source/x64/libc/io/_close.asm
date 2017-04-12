include io.inc
include errno.inc
include winbase.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

_close	PROC handle:SINT

	cmp	ecx,3
	jb	argerr
	cmp	ecx,_nfile
	jae	argerr
	lea	rax,_osfile
	test	BYTE PTR [rax+rcx],FH_OPEN
	jz	argerr

	mov	BYTE PTR [rax+rcx],0
	lea	rax,_osfhnd
	mov	rcx,[rax+rcx*8]
	CloseHandle( rcx )
	test	rax,rax
	jz	error
	xor	eax,eax
toend:
	ret
error:
	call	osmaperr
	jmp	toend
argerr:
	mov	errno,EBADF
	mov	oserrno,0
	xor	rax,rax
	jmp	toend
_close	ENDP

	END
