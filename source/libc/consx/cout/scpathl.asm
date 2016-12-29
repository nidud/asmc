include consx.inc
include string.inc

	.code

scpathl PROC USES esi edi edx ecx x, y, l, string:LPSTR
	local	pcx:DWORD
	local	lbuf[TIMAXSCRLINE]:BYTE
	movzx	esi,BYTE PTR l
	mov	al,' '
	lea	edi,lbuf
	mov	edx,edi
	mov	ecx,esi
	rep	stosb
	mov	edi,string
	strlen( edi )
	cmp	eax,esi
	jbe	lup
	mov	ecx,[edi]
	add	edi,eax
	sub	edi,esi
	add	edi,4
	cmp	ch,':'
	jne	@F
	mov	[edx],cl
	mov	[edx+1],ch
	add	edi,2
	add	edx,2
@@:	mov	ax,'.\'
	mov	[edx],al
	mov	[edx+1],ah
	mov	[edx+2],ah
	mov	[edx+3],al
	add	edx,4
	ALIGN	4
lup:
	mov	al,[edi]
	test	al,al
	jz	done
	mov	[edx],al
	inc	edi
	inc	edx
	jmp	lup
	ALIGN	4
done:
	movzx	eax,BYTE PTR x
	movzx	edx,BYTE PTR y
	shl	edx,16
	mov	dx,ax
	WriteConsoleOutputCharacter( hStdOutput, addr lbuf, esi, edx, addr pcx )
	mov	eax,pcx
	ret
scpathl ENDP

	END
