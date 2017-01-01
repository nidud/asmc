include consx.inc

	.code

	OPTION	WIN64:0, STACKBASE:rsp

rcbprcrc PROC USES rbx r1, r2, wbuf:PVOID, cols
	mov	eax,r9d
	add	eax,eax
	mov	bx,cx
	add	bx,dx
	mul	bh
	movzx	ebx,bl
	add	eax,ebx
	add	eax,ebx
	add	rax,r8
	ret
rcbprcrc ENDP

	END
