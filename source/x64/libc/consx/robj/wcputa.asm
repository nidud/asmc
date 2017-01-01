include consx.inc

wcputxg proto

	.code

	OPTION	WIN64:0, STACKBASE:rsp

wcputa	proc uses rbx wp:PVOID, l, attrib
	mov	rbx,rcx
	mov	eax,r8d
	mov	ecx,edx
	and	eax,00FFh
	call	wcputxg
	ret
wcputa	endp

	END
