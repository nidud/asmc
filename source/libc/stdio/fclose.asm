include stdio.inc
include io.inc

	.code

	option stackbase:esp

fclose	proc uses ebx fp:LPFILE
	mov	ebx,fp
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
	ret
error:
	mov	eax,-1
	jmp	toend
fclose	ENDP

	END
