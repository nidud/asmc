include io.inc
include errno.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

_lseek	PROC handle:SINT, offs:QWORD, pos:UINT
	.if	r8d == SEEK_SET
		and	rdx,0FFFFFFFFh
	.endif
	_lseeki64( ecx, rdx, r8d )
	ret
_lseek	ENDP

	END
