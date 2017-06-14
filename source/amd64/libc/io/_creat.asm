include io.inc
include fcntl.inc
include stat.inc
include errno.inc
include winbase.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

_creat	PROC path:LPSTR, flag:UINT
	mov eax,edx
	mov r10d,_A_NORMAL
	mov edx,O_WRONLY
	and eax,S_IREAD or S_IWRITE
	.repeat
	    .if eax != S_IWRITE
		mov edx,O_RDWR
		.if eax != S_IREAD or S_IWRITE
		    .if eax == S_IREAD
			mov edx,O_RDONLY
			mov r10d,_A_RDONLY
		    .else
			mov errno,EINVAL
			xor eax,eax
			mov oserrno,eax
			dec eax
			.break
		    .endif
		.endif
	    .endif
	    xor r8d,r8d
	    .if ecx == O_RDONLY
		mov r8d,FILE_SHARE_READ
	    .endif
	    _osopenA(rcx, edx, r8d, 0, A_CREATETRUNC, r10d)
	.until 1
	ret
_creat	ENDP

	END
