include stdio.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

fgetc	PROC fp:LPFILE

	dec	[rcx].S_FILE.iob_cnt
	jl	fbuf
	inc	[rcx].S_FILE.iob_ptr
	mov	rax,[rcx].S_FILE.iob_ptr
	movzx	rax,byte ptr [rax-1]
toend:
	ret
fbuf:
	_filbuf( rcx )
	jmp	toend
fgetc	ENDP

	END
