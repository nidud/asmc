include stdio.inc

lastiob equ (offset _iob + (_NSTREAM_ * (SIZE S_FILE)))

	.code

_getst	PROC
	mov	edx,offset _iob
	.repeat
		xor	eax,eax
		.if	!( [edx].S_FILE.iob_flag & _IOREAD or _IOWRT or _IORW )
			mov	[edx].S_FILE.iob_cnt,eax
			mov	[edx].S_FILE.iob_flag,eax
			mov	[edx].S_FILE.iob_ptr,eax
			mov	[edx].S_FILE.iob_base,eax
			dec	eax
			mov	[edx].S_FILE.iob_file,eax
			mov	eax,edx
			.break
		.endif
		add	edx,SIZE S_FILE
	.until	edx == lastiob
	ret
_getst	ENDP

	END
