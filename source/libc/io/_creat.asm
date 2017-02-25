include io.inc
include fcntl.inc
include stat.inc
include errno.inc

	.code

_creat	PROC path:LPSTR, flag

	mov edx,_A_NORMAL
	mov ecx,O_WRONLY
	mov eax,flag
	and eax,S_IREAD or S_IWRITE

	.repeat
		.if eax != S_IWRITE

			mov ecx,O_RDWR
			.if eax != S_IREAD or S_IWRITE

				.if eax == S_IREAD

					mov eax,O_RDONLY
					mov edx,_A_RDONLY
				.else
					mov errno,EINVAL
					xor eax,eax
					mov oserrno,eax
					dec eax
					.break
				.endif
			.endif
		.endif
		osopen( path, edx, ecx, A_CREATETRUNC )
	.until	1
	ret

_creat	ENDP

	END
