include consx.inc

	.code

	OPTION	WIN64:0, STACKBASE:rsp

wcputw	PROC USES rdi b:PVOID, l, w
	mov	eax,r8d
	mov	ecx,edx
	mov	rdi,rcx
	.if	ah
		rep	stosw
	.else
		.repeat
			stosb
			inc rdi
		.untilcxz
	.endif
	ret
wcputw	ENDP

	END
