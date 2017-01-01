include stdio.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

fputc	PROC char: SIZE_T, fp: LPFILE

	dec	[rdx].S_FILE.iob_cnt
	jl	flush
	mov	r8,[rdx].S_FILE.iob_ptr
	inc	[rdx].S_FILE.iob_ptr
	mov	rax,rcx
	mov	[r8],al
toend:
	ret
flush:
	_flsbuf( rcx, rdx )
	jmp	toend
fputc	ENDP

	END
