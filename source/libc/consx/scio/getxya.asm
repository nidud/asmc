include consx.inc

	.code

getxya	PROC USES ecx edx x, y
	movzx	eax,BYTE PTR y
	shl	eax,16
	mov	al,BYTE PTR x	; COORD
	push	eax
	mov	edx,esp		; lpAttribute
	push	eax
	mov	ecx,esp		; lpNumberOfAttributesRead
	ReadConsoleOutputAttribute( hStdOutput, edx, 1, eax, ecx )
	pop	eax		; <1>
	pop	eax		; Attribute
	and	eax,00FFh
	ret
getxya	ENDP

	END
