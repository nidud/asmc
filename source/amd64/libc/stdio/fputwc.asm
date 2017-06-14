include stdio.inc

    option win64:2

	.code

fputwc	PROC wc:wint_t, fp:LPFILE

	sub [rdx]._iobuf._cnt,2
	.ifl
		_flswbuf(ecx, rdx)
	.else
		mov rax,[rdx]._iobuf._ptr
		add [rdx]._iobuf._ptr,2
		mov [rax],cx
	.endif
	ret

fputwc	ENDP

	END
