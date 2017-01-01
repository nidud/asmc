include consx.inc
include io.inc
include stdio.inc
include string.inc

	.data
	cp_ok db '&Ok',0
	cp_er db 'Error',0

	.code

	OPTION	PROC: PRIVATE

center_text:
	.if	byte ptr [rdi]
		mul	rcx
		lea	rax,[rax*2+8]
		add	rbx,rax
		sub	rcx,8
		mov	r8d,ecx
		wcenter( rbx, r8d, rdi )
	.endif
	ret

MAXLINES equ 17


msgbox PROC USES rsi rdi rbx rbp r12 r13 r14 r15 Caption:LPSTR, flag:DWORD, string:LPSTR

	local	dobj:S_DOBJ
	local	tobj:S_TOBJ
	;local	cols:dword

	mov	r12b,at_background[B_Title]
	mov	dobj.dl_flag,dx

	mov	rdi,r8
	strlen( rcx )
	xor	rsi,rsi
	mov	rbx,rax

	.if !strchr( rdi, 10 )
		.if strlen( rdi ) > rbx
			mov rbx,rax
		.endif
	.endif


	.if byte ptr [rdi]

		.while	strchr( rdi, 10 )

			mov	rdx,rax
			sub	rdx,rdi
			.if	rdx >= rbx
				mov rbx,rdx
			.endif
			inc	esi
			lea	rdi,[rax+1]
			.break	.if esi == MAXLINES
		.endw
	.endif


	.if strlen( rdi ) >= rbx
		mov	rbx,rax
	.endif

	mov	dl,2
	mov	dh,76
	.if	bl && bl < 70
		mov	dh,bl
		add	dh,8
		mov	dl,80
		sub	dl,dh
		shr	dl,1
	.endif
	.if	dh < 40
		mov	dx,2814h
	.endif

	mov	dobj.dl_rect.rc_x,dl
	mov	dobj.dl_rect.rc_y,7
	mov	eax,esi
	add	al,6
	mov	dobj.dl_rect.rc_row,al
	mov	dobj.dl_rect.rc_col,dh
	mov	dobj.dl_count,1
	mov	dobj.dl_index,0
	add	al,7
	.if	eax > _scrrow
		mov dobj.dl_rect.rc_y,1
	.endif
	lea	rax,tobj
	mov	dobj.dl_object,rax
	mov	tobj.to_flag,_O_PBUTT
	mov	al,dh
	shr	al,1
	sub	al,3
	mov	tobj.to_rect.rc_x,al
	mov	eax,esi
	add	al,4
	mov	tobj.to_rect.rc_y,al
	mov	tobj.to_rect.rc_row,1
	mov	tobj.to_rect.rc_col,6
	mov	tobj.to_ascii,'O'
	mov	al,at_background[B_Dialog]
	or	al,at_foreground[F_Dialog]
	.if	dobj.dl_flag & _D_STERR
		mov	at_background[B_Title],70h
		mov	al,at_background[B_Error]
		or	al,7;at_foreground[F_Desktop]
		or	tobj.to_flag,_O_DEXIT
	.endif
	mov	dl,al
	.if	dlopen( addr dobj, edx, Caption )

		mov	rdi,string
		mov	rsi,rdi
		movzx	eax,dobj.dl_rect.rc_col
		mov	r13d,eax
		mov	ebp,2

		.while	byte ptr [rsi]

			strchr( rdi, 10 )
			mov	rsi,rax
			.break .if !rax
			mov	byte ptr [rsi],0
			inc	rsi
			mov	ecx,r13d
			mov	eax,ebp
			mov	rbx,dobj.dl_wp
			call	center_text
			mov	rdi,rsi
			inc	ebp
			.break	.if ebp == MAXLINES+2
		.endw

		rcbprc( tobj.to_rect, dobj.dl_wp, r13d )
		movzx	r8d,tobj.to_rect.rc_col
		wcpbutt( rax, r13d, r8d, addr cp_ok )

		mov	at_background[B_Title],r12b
		mov	ecx,r13d
		mov	eax,ebp
		mov	rbx,dobj.dl_wp
		call	center_text
		dlmodal( addr dobj )
	.endif
	ret
msgbox	ENDP

	OPTION	PROC: PUBLIC

ermsg	PROC USES rbx wtitle:LPSTR, format:LPSTR, argptr:VARARG
	ftobufin( format, addr argptr )
	mov	rax,wtitle
	.if	!rax
		lea rax,cp_er
	.endif
	msgbox( rax, _D_STDERR, addr _bufin )
	xor	rax,rax
	ret
ermsg	ENDP

stdmsg	PROC wtitle:LPSTR, format:LPSTR, argptr:VARARG
	ftobufin( format, addr argptr )
	msgbox( wtitle, _D_STDDLG, addr _bufin )
	xor	rax,rax
	ret
stdmsg	ENDP

	END
