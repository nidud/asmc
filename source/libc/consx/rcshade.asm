include consx.inc
include alloc.inc

S_SHADE STRUC
dlwp_B	dd ?
sbuf_B	dd ?
sbuf_R	dd ?
rect_B	S_RECT <?>
rect_R	S_RECT <?>
S_SHADE ENDS

	.code

	_FG_DEACTIVE	equ 8
	option	cstack:on
	assume	edi:ptr S_SHADE

RCInitShade:
	push	ebp
	mov	ebp,esp
	mov	[edi].rect_B,eax
	mov	[edi].rect_R,eax
	shr	eax,16
	push	eax
	mov	[edi].rect_R.rc_col,2
	dec	[edi].rect_R.rc_row
	inc	[edi].rect_R.rc_y
	add	[edi].rect_R.rc_x,al
	add	[edi].rect_B.rc_y,ah
	mov	[edi].rect_B.rc_row,1
	add	[edi].rect_B.rc_x,2
	mul	ah
	add	eax,eax
	add	eax,ecx
	mov	[edi].dlwp_B,eax
	pop	eax
	movzx	esi,al	; rc.rc_col
	movzx	eax,ah	; rc.rc_row
	shl	eax,2
	add	esi,esi
	add	eax,esi
	alloca( eax )
	mov	[edi].sbuf_B,eax
	add	eax,esi
	mov	[edi].sbuf_R,eax
	rcread( [edi].rect_R, [edi].sbuf_R )
	test	eax,eax
	jz	toend
	rcread( [edi].rect_B, [edi].sbuf_B )
	test	eax,eax
	jz	toend
	mov	edx,[edi].dlwp_B
	mov	esi,[edi].sbuf_B
	inc	esi
	movzx	ecx,[edi].rect_R.rc_row
	add	ecx,ecx
	add	cl,[edi].rect_B.rc_col
	test	ebx,ebx
	jz	clear_shade
@@:
	mov	al,[esi]
	mov	[edx],al
	mov	al,_FG_DEACTIVE
	mov	[esi],al
	add	esi,2
	inc	edx
	dec	ecx
	jnz	@B
	jmp	write_shade
clear_shade:
	mov	al,[edx]
	mov	[esi],al
	add	esi,2
	inc	edx
	dec	ecx
	jnz	clear_shade
write_shade:
	rcwrite( [edi].rect_R, [edi].sbuf_R )
	rcwrite( [edi].rect_B, [edi].sbuf_B )
toend:
	mov	esp,ebp
	pop	ebp
	ret

rcsetshade proc uses esi edi ebx ecx edx rc, wp:PVOID
  local sh:S_SHADE
	lea	edi,sh
	mov	eax,rc
	mov	ecx,wp
	mov	ebx,1
	call	RCInitShade
	ret
rcsetshade endp

rcclrshade proc uses esi edi ebx rc, wp:PVOID
  local sh:S_SHADE
	lea	edi,sh
	mov	eax,rc
	mov	ecx,wp
	xor	ebx,ebx
	call	RCInitShade
	ret
rcclrshade endp

	END
