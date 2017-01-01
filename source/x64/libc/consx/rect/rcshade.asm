include consx.inc
include alloc.inc

S_SHADE STRUC
dlwp_B	dq ?
sbuf_B	dq ?
sbuf_R	dq ?
rect_B	S_RECT <?>
rect_R	S_RECT <?>
S_SHADE ENDS

	.code

	_FG_DEACTIVE	equ 8
	ASSUME	rdi:	ptr S_SHADE

	option	win64:2

RCShade PROC PRIVATE USES rsi rdi rbx rc:S_RECT, wp:PVOID, set_shade:byte
  local shade:S_SHADE


	mov	eax,ecx
	mov	ebx,r8d
	lea	rdi,shade

	mov	[rdi].rect_B,eax
	mov	[rdi].rect_R,eax
	shr	eax,16
	mov	rsi,rax
	mov	[rdi].rect_R.rc_col,2
	dec	[rdi].rect_R.rc_row
	inc	[rdi].rect_R.rc_y
	add	[rdi].rect_R.rc_x,al
	add	[rdi].rect_B.rc_y,ah
	mov	[rdi].rect_B.rc_row,1
	add	[rdi].rect_B.rc_x,2
	mul	ah
	add	eax,eax
	add	rax,rdx
	mov	[rdi].dlwp_B,rax
	mov	rax,rsi
	movzx	esi,al	; rc.rc_col
	movzx	eax,ah	; rc.rc_row
	shl	rax,2
	add	esi,esi
	add	eax,esi
	alloca( eax )
	mov	[rdi].sbuf_B,rax
	add	rax,rsi
	mov	[rdi].sbuf_R,rax

	.if	rcread( [rdi].rect_R, rax )

		.if	rcread( [rdi].rect_B, [rdi].sbuf_B )

			mov	rdx,[rdi].dlwp_B
			mov	rsi,[rdi].sbuf_B
			inc	rsi
			movzx	ecx,[rdi].rect_R.rc_row
			add	ecx,ecx
			add	cl,[rdi].rect_B.rc_col

			.if	bl
				.repeat
					mov	al,[rsi]
					mov	[rdx],al
					mov	al,_FG_DEACTIVE
					mov	[rsi],al
					add	rsi,2
					inc	rdx
				.untilcxz
			.else
				.repeat
					mov	al,[rdx]
					mov	[rsi],al
					add	rsi,2
					inc	rdx
				.untilcxz
			.endif

			rcwrite( [rdi].rect_R, [rdi].sbuf_R )
			rcwrite( [rdi].rect_B, [rdi].sbuf_B )
		.endif
	.endif
	ret
RCShade endp

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

rcsetshade proc rc, wp:PVOID
	RCShade( ecx, rdx, 1 )
	ret
rcsetshade endp

rcclrshade proc rc, wp:PVOID
	RCShade( ecx, rdx, 0 )
	ret
rcclrshade endp

	END
