include stdio.inc
include alloc.inc

	.code

_freebuf PROC fp:LPFILE
	mov	ecx,fp
	mov	eax,[ecx]._iobuf._flag
	.if	eax & _IOREAD or _IOWRT or _IORW
		.if	eax & _IOMYBUF
			free( [ecx]._iobuf._base )
			xor	eax,eax
			mov	ecx,fp
			mov	[ecx]._iobuf._ptr,eax
			mov	[ecx]._iobuf._base,eax
			mov	[ecx]._iobuf._flag,eax
			mov	[ecx]._iobuf._bufsiz,eax
			mov	[ecx]._iobuf._cnt,eax
		.endif
	.endif
	ret
_freebuf ENDP

	END
