include stdio.inc

	.code

_ftbuf	PROC USES rsi rdi flag:UINT, fp:LPFILE

	mov rsi,rdx
	mov edi,[rsi]._iobuf._flag
	.if ecx
		.if edi & _IOFLRTN

			fflush( rsi )

			and edi,not (_IOYOURBUF or _IOFLRTN)
			mov [rsi]._iobuf._flag,edi
			xor eax,eax
			mov [rsi]._iobuf._ptr,rax
			mov [rsi]._iobuf._base,rax
			mov [rsi]._iobuf._bufsiz,eax
		.endif
	.else
		and edi,_IOFLRTN
		.ifnz
			fflush( rsi )
		.endif
	.endif
	ret
_ftbuf	ENDP

	END
