include stdio.inc

	.code

fputc	PROC char:SIZE_T, fp:LPFILE
	mov	eax,fp
	dec	[eax].S_FILE.iob_cnt
	jl	flush
	mov	edx,[eax].S_FILE.iob_ptr
	inc	[eax].S_FILE.iob_ptr
	mov	eax,char
	mov	[edx],al
toend:
	ret
flush:
	_flsbuf( char, eax )
	jmp	toend
fputc	ENDP

	END
