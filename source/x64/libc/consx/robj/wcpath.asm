include consx.inc
include string.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

wcpath	PROC USES rsi rdi b:PVOID, l, p:PVOID
	__wcpath( rcx, edx, r8 )
	.if	ecx
		mov	rsi,rdx
		mov	rdi,rax
		.repeat
			movsb
			inc rdi
		.untilcxz
	.endif
	ret
wcpath	ENDP

	END
