include consx.inc
include string.inc

	.code

scputal PROC USES esi edx ecx eax x, y, l, attrib:PVOID
	local	pcx:DWORD
	local	lbuf[TIMAXSCRLINE]:WORD
	movzx	ecx,BYTE PTR l
	xor	eax,eax
	lea	edx,lbuf
	mov	esi,attrib
@@:
	mov	al,[esi]
	mov	[edx],ax
	add	edx,2
	inc	esi
	dec	ecx
	jnz	@B
	movzx	eax,BYTE PTR x
	movzx	edx,BYTE PTR y
	cmp	edx,_scrrow
	ja	toend
	shl	edx,16
	add	edx,eax
	movzx	ecx,BYTE PTR l
	add	eax,ecx
	cmp	eax,_scrcol
	jbe	@F
	sub	eax,ecx
	mov	ecx,_scrcol
	sub	ecx,eax
	jle	toend
@@:
	WriteConsoleOutputAttribute( hStdOutput, addr lbuf, ecx, edx, addr pcx )
toend:
	ret
scputal ENDP

	END
