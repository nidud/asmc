include stdio.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

fgetc	PROC fp:LPFILE
	mov	eax,[esp+4]
	dec	[eax].S_FILE.iob_cnt
	jl	fbuf
	inc	[eax].S_FILE.iob_ptr
	mov	eax,[eax].S_FILE.iob_ptr
	movzx	eax,byte ptr [eax-1]
toend:
	ret	4
fbuf:
	_filbuf( eax )
	jmp	toend
fgetc	ENDP

	END
