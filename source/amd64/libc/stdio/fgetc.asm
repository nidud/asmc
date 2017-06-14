include stdio.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

fgetc	PROC fp:LPFILE

	dec	[rcx]._iobuf._cnt
	jl	fbuf
	inc	[rcx]._iobuf._ptr
	mov	rax,[rcx]._iobuf._ptr
	movzx	rax,byte ptr [rax-1]
toend:
	ret
fbuf:
	_filbuf( rcx )
	jmp	toend
fgetc	ENDP

	END
