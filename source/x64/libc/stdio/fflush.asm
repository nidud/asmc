include stdio.inc
include io.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp
	ASSUME	rbx: LPFILE

fflush	PROC USES rbx rdi rsi r12 fp:LPFILE

	mov	rbx,rcx
	xor	rsi,rsi
	mov	eax,[rbx].iob_flag
	mov	edi,eax
	and	eax,_IOREAD or _IOWRT

	.if	eax == _IOWRT && edi & _IOMYBUF or _IOYOURBUF

		mov	r12,[rbx].iob_ptr
		sub	r12,[rbx].iob_base
		jle	toend

		.if	_write( [rbx].iob_file, [rbx].iob_base, r12 ) == r12

			mov	eax,[rbx].iob_flag
			.if	eax & _IORW

				and	eax,not _IOWRT
				mov	[rbx].iob_flag,eax
			.endif
		.else
			or	edi,_IOERR
			mov	[rbx].iob_flag,edi
			mov	rsi,-1
		.endif
	.endif
toend:
	mov	rax,[rbx].iob_base
	mov	[rbx].iob_ptr,rax
	mov	[rbx].iob_cnt,0
	mov	rax,rsi
	ret
fflush	ENDP

	END
