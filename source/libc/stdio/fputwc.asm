include stdio.inc

	.code

fputwc	PROC wc:wint_t, fp:LPFILE

	movzx	eax,wc
	mov	ecx,fp
	dec	[ecx]._iobuf._cnt
	.ifl
		_flswbuf(eax, ecx)
	.else
		mov edx,[ecx]._iobuf._ptr
		add [ecx]._iobuf._ptr,2
		mov [edx],ax
	.endif
	ret

fputwc	ENDP

	END
