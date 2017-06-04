include stdio.inc
include io.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

fclose	PROC fp:LPFILE
	push	ebx
	mov	ebx,[esp+8]
	mov	eax,[ebx]._iobuf._flag
	and	eax,_IOREAD or _IOWRT or _IORW
	jz	error
	fflush( ebx )
	push	eax
	_freebuf( ebx )
	xor	eax,eax
	mov	[ebx]._iobuf._flag,eax
	mov	ecx,[ebx]._iobuf._file
	dec	eax
	mov	[ebx]._iobuf._file,eax
	_close( ecx )
	test	eax,eax
	pop	eax
	jnz	error
toend:
	pop	ebx
	ret
error:
	mov	eax,-1
	jmp	toend
fclose	ENDP

	END
