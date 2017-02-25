include stdio.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

fgetc	PROC fp:LPFILE
	mov	eax,[esp+4]
	dec	[eax]._iobuf._cnt
	jl	fbuf
	add	[eax]._iobuf._ptr,1
	mov	eax,[eax]._iobuf._ptr
	movzx	eax,byte ptr [eax-1]
toend:
	ret	4
fbuf:
	_filbuf( eax )
	jmp	toend
fgetc	ENDP

	END
