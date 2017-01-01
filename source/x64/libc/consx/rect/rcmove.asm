include consx.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

rcmove	PROC USES rsi rdi rbx r12 pRECT:PVOID, wp:PVOID, flag, x, y

	mov	rsi,rcx
	mov	rdi,rdx
	mov	r12,r8
	mov	bl,BYTE PTR x
	mov	bh,BYTE PTR y
	mov	ecx,[rsi]

	.if	rchide( ecx, r12d, rdi )

		mov	[rsi],bx
		mov	ecx,[rsi]
		and	r12d,not _D_ONSCR
		rcshow( ecx, r12d, r12 )
	.endif
	mov	eax,[rsi]
	ret
rcmove	ENDP

	END
