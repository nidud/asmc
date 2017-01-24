include consx.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

dlmodal PROC USES rbx dobj:PTR S_DOBJ
	mov	rbx,rcx
	dlevent( rcx )
	xchg	rax,rbx
	dlclose( rax )
	mov	rax,rbx
	test	rax,rax
	ret
dlmodal ENDP

	END
