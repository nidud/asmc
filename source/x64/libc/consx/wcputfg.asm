include consx.inc

wcputxg PROTO

	.code

	OPTION	WIN64:0, STACKBASE:rsp

wcputfg PROC USES rbx wp:PVOID, l, attrib
	mov	eax,r8d
	mov	ah,70h
	and	al,0Fh
	mov	ecx,edx
	mov	rbx,rcx
	call	wcputxg
	ret
wcputfg ENDP

	END
