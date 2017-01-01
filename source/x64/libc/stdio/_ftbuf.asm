include stdio.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

_ftbuf	PROC USES rsi rdi flag:SIZE_T, fp:LPFILE

	mov	rsi,rdx
	mov	edi,[rsi].S_FILE.iob_flag
	.if	ecx
		.if	edi & _IOFLRTN

			fflush( rsi )

			and	edi,not (_IOYOURBUF or _IOFLRTN)
			mov	[rsi].S_FILE.iob_flag,edi
			xor	eax,eax
			mov	[rsi].S_FILE.iob_ptr,rax
			mov	[rsi].S_FILE.iob_base,rax
			mov	[rsi].S_FILE.iob_bufsize,eax
		.endif
	.else
		and	edi,_IOFLRTN
		.if	!ZERO?
			fflush( rsi )
		.endif
	.endif
	ret
_ftbuf	ENDP

	END
