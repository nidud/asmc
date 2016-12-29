include stdio.inc
include io.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

fclose	PROC fp:LPFILE
	push	ebx
	mov	ebx,[esp+8]
	mov	eax,[ebx].S_FILE.iob_flag
	and	eax,_IOREAD or _IOWRT or _IORW
	jz	error
	fflush( ebx )
	push	eax
	_freebuf( ebx )
	xor	eax,eax
	mov	[ebx].S_FILE.iob_flag,eax
	mov	ecx,[ebx].S_FILE.iob_file
	dec	eax
	mov	[ebx].S_FILE.iob_file,eax
	_close( ecx )
	test	eax,eax
	pop	eax
	jnz	error
toend:
	pop	ebx
	ret	4
error:
	mov	eax,-1
	jmp	toend
fclose	ENDP

	END
