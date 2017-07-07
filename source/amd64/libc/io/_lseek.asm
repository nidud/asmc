include io.inc
include errno.inc

	.code

	option win64:rsp nosave

_lseek	PROC handle:SINT, offs:QWORD, pos:UINT
	.if r8d == SEEK_SET
		mov edx,edx
	.endif
	_lseeki64(ecx, rdx, r8d)
	ret
_lseek	ENDP

	END
