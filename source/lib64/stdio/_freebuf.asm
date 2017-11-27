include stdio.inc
include malloc.inc

	.code

	OPTION	WIN64:3, STACKBASE:rsp

_freebuf PROC fp:LPFILE

	mov	eax,[rcx]._iobuf._flag
	.if	eax & _IOREAD or _IOWRT or _IORW
		.if	eax & _IOMYBUF
			free( [rcx]._iobuf._base )
			xor	eax,eax
			mov	rcx,fp
			mov	[rcx]._iobuf._ptr,rax
			mov	[rcx]._iobuf._base,rax
			mov	[rcx]._iobuf._flag,eax
			mov	[rcx]._iobuf._bufsiz,eax
			mov	[rcx]._iobuf._cnt,eax
		.endif
	.endif
	ret
_freebuf ENDP

	END
