include stdio.inc
include io.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

fclose	PROC USES rsi rbx fp:LPFILE

	mov	rbx,rcx
	mov	eax,[rbx].S_FILE.iob_flag
	and	eax,_IOREAD or _IOWRT or _IORW
	jz	error
	fflush( rbx )
	mov	rsi,rax
	_freebuf( rbx )
	xor	eax,eax
	mov	[rbx].S_FILE.iob_flag,eax
	mov	ecx,[rbx].S_FILE.iob_file
	dec	eax
	mov	[rbx].S_FILE.iob_file,eax
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
