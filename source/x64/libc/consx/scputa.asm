include consx.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

scputa	PROC x, y, l, a
	local	pcx
	movzx	eax,cl
	mov	r10,r9
	movzx	r9d,dl
	shl	r9d,16
	mov	r9w,ax
	movzx	edx,r10b
	FillConsoleOutputAttribute( hStdOutput, edx, r8d, r9d, addr pcx )
	ret
scputa	ENDP

	END
