include io.inc
include fcntl.inc
include stat.inc
include errno.inc

	.code

_creat	PROC path:LPSTR, flag:SIZE_T
	mov	edx,_A_NORMAL
	mov	ecx,O_WRONLY
	mov	eax,flag
	and	eax,S_IREAD or S_IWRITE
	cmp	eax,S_IWRITE
	je	@F
	mov	ecx,O_RDWR
	cmp	eax,S_IREAD or S_IWRITE
	je	@F
	cmp	eax,S_IREAD
	jne	error
	mov	eax,O_RDONLY
	mov	edx,_A_RDONLY
@@:
	osopen( path, edx, ecx, A_CREATETRUNC )
toend:
	ret
error:
	mov	errno,EINVAL
	xor	eax,eax
	mov	oserrno,eax
	dec	eax
	jmp	toend
_creat	ENDP

	END
