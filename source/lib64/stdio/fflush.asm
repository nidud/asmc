include stdio.inc
include io.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp
	ASSUME	rbx: LPFILE

fflush	PROC USES rbx rdi rsi r12 fp:LPFILE

	mov	rbx,rcx
	xor	rsi,rsi
	mov	eax,[rbx]._flag
	mov	edi,eax
	and	eax,_IOREAD or _IOWRT

	.if	eax == _IOWRT && edi & _IOMYBUF or _IOYOURBUF

		mov	r12,[rbx]._ptr
		sub	r12,[rbx]._base
		jle	toend

		.if	_write( [rbx]._file, [rbx]._base, r12 ) == r12

			mov	eax,[rbx]._flag
			.if	eax & _IORW

				and	eax,not _IOWRT
				mov	[rbx]._flag,eax
			.endif
		.else
			or	edi,_IOERR
			mov	[rbx]._flag,edi
			mov	rsi,-1
		.endif
	.endif
toend:
	mov	rax,[rbx]._base
	mov	[rbx]._ptr,rax
	mov	[rbx]._cnt,0
	mov	rax,rsi
	ret
fflush	ENDP

	END
