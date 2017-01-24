include consx.inc

	.code

scputs	PROC USES esi edi edx ecx x, y, a, l, string:LPSTR
	local	bz:COORD
	local	rect:SMALL_RECT
	local	lbuf[TIMAXSCRLINE]:CHAR_INFO
	mov	edx,_scrcol
	movzx	ecx,BYTE PTR l
	movzx	eax,BYTE PTR x
	cmp	eax,edx
	ja	error
	test	ecx,ecx
	jz	@F
	cmp	ecx,edx
	jbe	limit2
@@:
	mov	ecx,edx
	sub	ecx,eax
limit2:
	add	eax,ecx
	cmp	eax,edx
	ja	error
	mov	esi,ecx
	movzx	eax,BYTE PTR a
	test	eax,eax
	jnz	@F
	getxya( x, y )
@@:
	mov	a,eax
	shl	eax,16
	mov	al,' '
	lea	edi,lbuf
	mov	ecx,esi
	rep	stosd
	mov	ecx,esi
	mov	esi,string
	lea	edi,lbuf
	jmp	lup
lf:
	lea	eax,[esi+1]
	mov	ecx,y
	inc	ecx
	scputs( x, ecx, a, l, eax )
	jmp	break
tab:
	add	edi,32
	and	edi,-32
	inc	esi
lup:
	mov	al,[esi]
	test	al,al
	jz	break
	cmp	al,9
	je	tab
	cmp	al,10
	je	lf
	inc	esi
	mov	[edi],al
	add	edi,SIZE CHAR_INFO
	dec	ecx
	jnz	lup
break:
	sub	esi,string
	jz	error
	mov	bz.x,si
	mov	bz.y,1
	movzx	eax,BYTE PTR x
	mov	rect.Left,ax
	add	eax,esi
	dec	eax
	mov	rect.Right,ax
	movzx	eax,BYTE PTR y
	mov	rect.Top,ax
	mov	rect.Bottom,ax
	WriteConsoleOutput( hStdOutput, addr lbuf, bz, 0, addr rect )
	mov	eax,esi
toend:
	ret
error:
	xor	eax,eax
	jmp	toend
scputs	ENDP

	END
