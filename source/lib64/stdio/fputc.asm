include stdio.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

fputc	PROC char:SINT, fp: LPFILE

	dec	[rdx]._iobuf._cnt
	jl	flush
	mov	r8,[rdx]._iobuf._ptr
	inc	[rdx]._iobuf._ptr
	mov	rax,rcx
	mov	[r8],al
toend:
	ret
flush:
	_flsbuf( ecx, rdx )
	jmp	toend
fputc	ENDP

	END
