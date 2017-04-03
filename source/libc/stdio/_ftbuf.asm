include stdio.inc

	.code

_ftbuf	PROC flag:ULONG, fp:LPFILE

	mov edx,fp
	assume edx:ptr _iobuf

	mov eax,[edx]._flag
	.if flag

		.if eax & _IOFLRTN

			push eax
			fflush( edx )
			pop eax

			and eax,not (_IOYOURBUF or _IOFLRTN)
			mov edx,fp
			mov [edx]._flag,eax
			xor eax,eax
			mov [edx]._ptr,eax
			mov [edx]._base,eax
			mov [edx]._bufsiz,eax
		.endif
	.else
		and eax,_IOFLRTN
		.ifnz
			fflush( edx )
		.endif
	.endif
	ret

_ftbuf	ENDP

	END
