include stdio.inc

	.code

	OPTION	WIN64:0, STACKBASE:rsp

_getst	PROC
	lea	rdx,_iob
	lea	r10,[rdx+(_NSTREAM_ * (SIZE S_FILE))]
	.repeat
		xor	eax,eax
		.if	!( [rdx].S_FILE.iob_flag & _IOREAD or _IOWRT or _IORW )
			mov	[rdx].S_FILE.iob_cnt,eax
			mov	[rdx].S_FILE.iob_flag,eax
			mov	[rdx].S_FILE.iob_ptr,rax
			mov	[rdx].S_FILE.iob_base,rax
			dec	eax
			mov	[rdx].S_FILE.iob_file,eax
			mov	rax,rdx
			.break
		.endif
		add	rdx,SIZE S_FILE
	.until	rdx >= r10
	ret
_getst	ENDP

	END
