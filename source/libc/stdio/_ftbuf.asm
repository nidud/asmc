include stdio.inc

	.code

_ftbuf	PROC flag:ULONG, fp:LPFILE
	mov	edx,fp
	mov	eax,[edx].S_FILE.iob_flag
	.if	flag
		.if	eax & _IOFLRTN
			push	eax
			fflush( edx )
			pop	eax
			and	eax,not (_IOYOURBUF or _IOFLRTN)
			mov	edx,fp
			mov	[edx].S_FILE.iob_flag,eax
			xor	eax,eax
			mov	[edx].S_FILE.iob_ptr,eax
			mov	[edx].S_FILE.iob_base,eax
			mov	[edx].S_FILE.iob_bufsize,eax
		.endif
	.else
		and	eax,_IOFLRTN
		.if	!ZERO?
			fflush( edx )
		.endif
	.endif
	ret
_ftbuf	ENDP

	END
