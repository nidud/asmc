include io.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

_eof	PROC USES rsi rdi handle:SINT

	mov	edi,ecx
	_lseeki64( ecx, 0, SEEK_CUR )
	mov	rsi,rax
	_lseeki64( edi, 0, SEEK_END )

	cmp	rax,rsi
	jne	not_eof
	cmp	rax,-1
	je	toend
	mov	eax,1
	jmp	toend
not_eof:
	_lseeki64( edi, rsi, SEEK_SET )
	xor	eax,eax
toend:
	ret
_eof	ENDP

	END
