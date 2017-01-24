include consx.inc

	.code

	OPTION	WIN64:0, STACKBASE:rsp

wcmemset PROC USES rdi string:PVOID, val, count
	mov	rdi,rcx
	mov	eax,edx
	mov	ecx,r8d
	rep	stosw
	ret
wcmemset ENDP

	END
