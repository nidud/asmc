include stdio.inc
include io.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

fclose	PROC USES rsi rbx fp:LPFILE

	mov	rbx,rcx
	mov	eax,[rbx]._iobuf._flag
	and	eax,_IOREAD or _IOWRT or _IORW
	jz	error
	fflush( rbx )
	mov	rsi,rax
	_freebuf( rbx )
	xor	eax,eax
	mov	[rbx]._iobuf._flag,eax
	mov	ecx,[rbx]._iobuf._file
	dec	eax
	mov	[rbx]._iobuf._file,eax
	_close( ecx )
	test	rax,rax
	mov	rax,rsi
	jnz	error
toend:
	ret
error:
	mov	rax,-1
	jmp	toend
fclose	ENDP

	END
