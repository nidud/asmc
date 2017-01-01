include consx.inc
include direct.inc
include string.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

scpath PROC USES rsi rdi rbx rbp r12 r13 x, y, l, string:LPSTR
local	b[16]:BYTE
	mov	rbx,rcx
	mov	r12,rdx
	mov	r13,r8
	mov	rsi,r9
	lea	rdi,b
	xor	rbp,rbp
	.if	strlen( rsi ) > r13
		mov	ecx,[rsi]
		add	rsi,rax
		sub	rsi,r13
		mov	ebp,4
		mov	eax,'\..\'
		.if	ch == ':'
			mov	[rdi+2],eax
			mov	[rdi],cx
			add	rbp,2
		.else
			mov	[rdi],eax
		.endif
		sub	eax,eax
		mov	[rdi+rbp],al
		scputs( ebx, r12d, eax, eax, rdi )
		add	rsi,rbp
		add	rbx,rbp
	.endif
	scputs( ebx, r12d, 0, 0, rsi )
	add	rax,rbp
	ret
scpath	ENDP

	END
