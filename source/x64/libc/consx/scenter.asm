include consx.inc
include string.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

scenter PROC USES rsi rdi rbx rbp x, y, l, s:LPSTR

	mov	rsi,r9
	mov	edi,ecx
	mov	ebx,edx
	mov	ebp,r8d

	.if	strlen( rsi ) > rbp
		add	rsi,rax
		sub	rsi,rbp
	.else
		mov	rcx,rax
		mov	rax,rbp
		sub	rax,rcx
		shr	rax,1
		add	edi,eax
		sub	ebp,eax
	.endif
	scputs( edi, ebx, 0, ebp, rsi )
	ret
scenter ENDP

	END
