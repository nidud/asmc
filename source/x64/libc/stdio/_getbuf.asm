include stdio.inc
include alloc.inc

	.code

	OPTION	WIN64:3, STACKBASE:rsp
	ASSUME	RDX: LPFILE

_getbuf PROC fp:LPFILE

	malloc( _INTIOBUF )

	mov	rdx,fp
	.if	rax
		or	[rdx]._flag,_IOMYBUF
		mov	[rdx]._bufsiz,_INTIOBUF
	.else
		or	[rdx]._flag,_IONBF
		mov	[rdx]._bufsiz,4
		lea	rax,[rdx]._charbuf
	.endif
	mov	[rdx]._ptr,rax
	mov	[rdx]._base,rax
	mov	[rdx]._cnt,0
	ret
_getbuf ENDP

	END
