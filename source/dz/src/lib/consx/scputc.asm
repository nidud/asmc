include consx.inc

	.code

scputc	PROC USES eax ecx edx x, y, l, char
	local	pcx
	movzx	ecx,BYTE PTR char
	movzx	eax,BYTE PTR x
	movzx	edx,BYTE PTR y
	shl	edx,16
	mov	dx,ax
	FillConsoleOutputCharacter( hStdOutput, ecx, l, edx, addr pcx )
	ret
scputc	ENDP

	END
