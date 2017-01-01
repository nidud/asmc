include stdio.inc
include alloc.inc

	.code

	OPTION	WIN64:3, STACKBASE:rsp
	ASSUME	RDX: LPFILE

_getbuf PROC fp:LPFILE

	malloc( _INTIOBUF )

	mov	rdx,fp
	.if	rax
		or	[rdx].iob_flag,_IOMYBUF
		mov	[rdx].iob_bufsize,_INTIOBUF
	.else
		or	[rdx].iob_flag,_IONBF
		mov	[rdx].iob_bufsize,4
		lea	rax,[rdx].iob_charbuf
	.endif
	mov	[rdx].iob_ptr,rax
	mov	[rdx].iob_base,rax
	mov	[rdx].iob_cnt,0
	ret
_getbuf ENDP

	END
