include consx.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

rsmodal PROC USES rsi rdi robj:PTR S_ROBJ
	mov	rsi,rcx
	rsopen( rcx )
	jz	toend
	mov	rdi,rax
	rsevent(rsi,rax)
	mov	rsi,rax
	dlclose(rdi)
	mov	rax,rsi
	test	rax,rax
toend:
	ret
rsmodal ENDP

	END
