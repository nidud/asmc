include io.inc
include fcntl.inc
include stat.inc
include errno.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

_creat	PROC path:LPSTR, flag:UINT

	mov	eax,edx
	mov	edx,_A_NORMAL
	mov	r8d,O_WRONLY
	and	eax,S_IREAD or S_IWRITE
	cmp	eax,S_IWRITE
	je	@F
	mov	r8d,O_RDWR
	cmp	eax,S_IREAD or S_IWRITE
	je	@F
	cmp	eax,S_IREAD
	jne	error
	mov	r8d,O_RDONLY
	mov	edx,_A_RDONLY
@@:
	osopen( rcx, edx, r8d, A_CREATETRUNC )
toend:
	ret
error:
	mov	errno,EINVAL
	xor	eax,eax
	mov	oserrno,eax
	dec	rax
	jmp	toend
_creat	ENDP

	END
