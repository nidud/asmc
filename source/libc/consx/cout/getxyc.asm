include consx.inc
include io.inc

	.code

getxyc	proc uses ecx edx x, y
	movzx	eax,byte ptr y
	shl	eax,16
	mov	al,byte ptr x
	push	0
	mov	edx,esp ; lpNumberOfCharsRead
	push	0
	mov	ecx,esp ; lpCharacter
	ReadConsoleOutputCharacter( hStdOutput, ecx, 1, eax, edx )
	pop	eax
	pop	edx
	and	eax,00FFh
	ret
getxyc	endp

	END
