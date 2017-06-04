include consx.inc
include alloc.inc

rsunzipch PROTO
rsunzipat PROTO

	.code

rsopen	PROC USES esi edi ebx ecx edx idd:PTR S_ROBJ
	local	result
	mov	esi,idd
	xor	eax,eax
	mov	al,[esi].S_ROBJ.rs_rect.rc_x
	add	al,[esi].S_ROBJ.rs_rect.rc_col
	.if	al >= BYTE PTR _scrcol
		sub	al,BYTE PTR _scrcol
		sub	[esi].S_ROBJ.rs_rect.rc_x,al
	.endif
	mov	al,[esi].S_ROBJ.rs_rect.rc_y
	add	al,[esi].S_ROBJ.rs_rect.rc_row
	mov	ah,BYTE PTR _scrrow
	inc	ah
	.if	al >= ah
		sub	al,ah
		sub	[esi].S_ROBJ.rs_rect.rc_y,al
	.endif
	mov	ax,[esi+8]	; rc_rows * rc_cols
	mov	edx,eax
	mul	ah
	mov	idd,eax
	add	eax,eax		; WORD size
	mov	edi,eax
	.if	WORD PTR [esi+2] & _D_SHADE
		add	dl,dh
		add	dl,dh
		mov	dh,0
		sub	edx,2
		add	edi,edx
	.endif
	movzx	eax,WORD PTR [esi]
	malloc( eax )
	mov	result,eax
	mov	ebx,edi
	mov	edi,eax
	mov	edx,eax
	movzx	ecx,WORD PTR [esi]
	jz	toend
	sub	eax,eax
	shr	ecx,1
	rep	stosw
	mov	ecx,edx
	mov	edi,edx
	lodsw			; skip size
	; -- copy dialog
	lodsw			; .flag
	or	eax,_D_SETRC
	push	eax
	stosw			; .flag
	movsw			; .count + .index
	movsd			; .rect
	movzx	eax,BYTE PTR [esi-6]
	inc	eax
	shl	eax,4		; * size of objects (16)
	add	eax,ecx		; + adress
	stosd			; = .wp (32)
	xchg	edx,eax
	add	eax,16		; dialog + 16
	stosd			; = .object
	; -- copy objects
	add	edx,ebx		; end of wp = start of object alloc
	movzx	ebx,BYTE PTR [esi-6]
	.while	ebx
		movsd			; copy 8 byte
		movsd			; get alloc size of object
		movzx	eax,BYTE PTR [esi-6]
		shl	eax,4		; * 16
		.if	eax
			xchg	eax,edx ; offset of mem (.data)
			stosd
			add	edx,eax
			xor	eax,eax
		.else
			stosd
		.endif
		stosd
		dec	ebx
	.endw
	pop	eax
	push	edi
	inc	edi
	mov	ecx,idd
	.if	eax & _D_RESAT
		call rsunzipat
	.else
		call rsunzipch
	.endif
	pop	edi
	mov	ecx,idd
	call	rsunzipch
	mov	eax,result
	test	eax,eax
toend:
	ret
rsopen	ENDP

	END
