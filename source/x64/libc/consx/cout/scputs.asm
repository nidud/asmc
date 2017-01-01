include consx.inc

	.code

scputs	PROC USES rsi rdi x, y, a, l, string:LPSTR
local	bz:COORD,
	rect:SMALL_RECT,
	lbuf[TIMAXSCRLINE]:CHAR_INFO

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
	lea	rdi,lbuf
	mov	ecx,esi
	rep	stosd
	mov	ecx,esi
	mov	rsi,string
	lea	rdi,lbuf
	jmp	lup
lf:
	lea	rax,[rsi+1]
	mov	edx,y
	inc	edx
	scputs( x, edx, a, l, rax )
	jmp	break
tab:
	add	rdi,32
	and	rdi,-32
	inc	rsi
lup:
	mov	al,[rsi]
	test	al,al
	jz	break
	cmp	al,9
	je	tab
	cmp	al,10
	je	lf
	inc	rsi
	mov	[rdi],al
	add	rdi,SIZE CHAR_INFO
	dec	ecx
	jnz	lup
break:
	sub	rsi,string
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
