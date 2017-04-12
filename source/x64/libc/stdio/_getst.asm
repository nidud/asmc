include stdio.inc

	.code

	OPTION	WIN64:0, STACKBASE:rsp

_getst	PROC
	lea	rdx,_iob
	lea	r10,[rdx+(_NSTREAM_ * sizeof(_iobuf))]
	.repeat
		xor	eax,eax
		.if	!( [rdx]._iobuf._flag & _IOREAD or _IOWRT or _IORW )
			mov	[rdx]._iobuf._cnt,eax
			mov	[rdx]._iobuf._flag,eax
			mov	[rdx]._iobuf._ptr,rax
			mov	[rdx]._iobuf._base,rax
			dec	eax
			mov	[rdx]._iobuf._file,eax
			mov	rax,rdx
			.break
		.endif
		add	rdx,sizeof(_iobuf)
	.until	rdx >= r10
	ret
_getst	ENDP

	END
