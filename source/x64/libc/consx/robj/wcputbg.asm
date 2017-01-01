include consx.inc

wcputxg PROTO

	.code

	OPTION	WIN64:0, STACKBASE:rsp

wcputbg PROC USES rbx wp:PVOID, l, attrib
	mov	eax,r8d
	mov	ah,0Fh
	and	al,0F0h
	mov	ecx,edx
	mov	rbx,rcx
	call	wcputxg
	ret
wcputbg ENDP

	END
