include consx.inc

	.code

scputa	PROC USES eax edx ecx x, y, l, a
	local	pcx
	movzx	ecx,BYTE PTR a
	movzx	eax,BYTE PTR x
	movzx	edx,BYTE PTR y
	shl	edx,16
	mov	dx,ax
	FillConsoleOutputAttribute( hStdOutput, cx, l, edx, addr pcx )
	ret
scputa	ENDP

	END
