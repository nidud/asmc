include consx.inc

	.code

	OPTION	WIN64:0, STACKBASE:rsp

wcenter PROC USES rsi rdi rbx wp:PVOID, l:DWORD, string:LPSTR
	mov	rdi,rcx
	mov	rbx,rdx
	__wcpath( rcx, edx, r8 )
	.if	ecx
		mov	rsi,rdx
		.if	rdi == rax
			mov	eax,ebx
			sub	rax,rcx
			and	al,not 1
			add	rax,rdi
		.endif
		mov	rdi,rax
		.repeat
			mov	al,[rsi]
			mov	[rdi],al
			add	rdi,2
			add	rsi,1
		.untilcxz
	.endif
	ret
wcenter ENDP

	END
