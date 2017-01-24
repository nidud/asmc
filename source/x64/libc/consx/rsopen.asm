include consx.inc
include alloc.inc

rsunzipch PROTO
rsunzipat PROTO

	.code

	OPTION WIN64:2
	OPTION STACKBASE:rsp

rsopen	PROC USES rsi rdi rbx r12 r13 r14 r15 idd:PTR S_ROBJ

	mov	rsi,rcx
	;
	; Test range
	;
	mov	edx,_scrcol
	mov	ecx,_scrrow
	xor	eax,eax

	mov	al,[rsi].S_ROBJ.rs_rect.rc_x
	add	al,[rsi].S_ROBJ.rs_rect.rc_col
	.if	al >= dl
		sub	al,dl
		sub	[rsi].S_ROBJ.rs_rect.rc_x,al
	.endif
	mov	al,[rsi].S_ROBJ.rs_rect.rc_y
	add	al,[rsi].S_ROBJ.rs_rect.rc_row
	inc	cl
	.if	al >= cl
		sub	al,cl
		sub	[rsi].S_ROBJ.rs_rect.rc_y,al
	.endif

	mov	ax,[rsi+8]	; rows * cols
	mov	edx,eax
	mul	ah
	mov	ebp,eax
	add	eax,eax		; WORD size
	mov	ebx,eax
	.if	WORD PTR [rsi+2] & _D_SHADE
		add	dl,dh
		add	dl,dh
		mov	dh,0
		sub	edx,2
		add	ebx,edx
	.endif

	movzx	rax,[rsi].S_ROBJ.rs_memsize
	malloc( rax )
	jz	toend
	mov	r12,rax

	mov	rdi,rax
	movzx	rcx,[rsi].S_ROBJ.rs_memsize
	xor	rax,rax
	rep	stosb

	mov	rdi,r12
	add	rsi,2
	movsq			; copy dialog
	movzx	rax,[r12].S_DOBJ.dl_count
	inc	rax
	imul	rax,rax,sizeof(S_TOBJ)
	add	rax,r12		; + adress
	lea	r8,[rax+rbx]	; end of .wp = start of object alloc
	stosq			; .wp
	lea	rax,[r12+sizeof(S_DOBJ)]
	stosq			; .object
	;
	; -- copy objects
	;
	movzx	ebx,[r12].S_DOBJ.dl_count
	.while	ebx
		movsq			; copy 8 byte
		movzx	rax,BYTE PTR [rsi-6]
		shl	rax,4
		.if	rax
			xchg	rax,r8	; offset of mem (.data)
			stosq
			add	r8,rax
			xor	rax,rax
		.else
			stosq
		.endif
		stosq
		dec	ebx
	.endw

	mov	eax,[r12]
	or	eax,_D_SETRC
	mov	[r12],eax
	mov	rbx,rdi
	inc	rdi
	mov	rcx,rbp
	.if	eax & _D_RESAT
		call rsunzipat
	.else
		call rsunzipch
	.endif
	mov	rdi,rbx
	mov	rcx,rbp
	call	rsunzipch
	mov	rax,r12
	test	rax,rax
toend:
	ret
rsopen	ENDP

	END
