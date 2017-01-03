; _OUTPUT.ASM--
; Copyright (C) 2015 Doszip Developers

include stdio.inc
include math.inc

PUBLIC output_flush
;public output_proctab
;public output_getd
;public output_getw

BUFFERSIZE	equ 512		; ANSI-specified minimum is 509

FLAG_SIGN	equ 0001h	; put plus or minus in front
FLAG_SIGNSP	equ 0002h	; put space or minus in front
FLAG_LEFT	equ 0004h	; left justify
FLAG_LEADZERO	equ 0008h	; pad with leading zeros
FLAG_LONG	equ 0010h	; long value given
FLAG_SHORT	equ 0020h	; short value given
FLAG_SIGNED	equ 0040h	; signed data given
FLAG_ALTERNATE	equ 0080h	; alternate form requested
FLAG_NEGATIVE	equ 0100h	; value is negative
FLAG_FORCEOCTAL equ 0200h	; force leading '0' for octals

	.data

cl_table label BYTE
	db	 06h, 00h, 00h, 06h, 00h, 01h, 00h, 00h
	db	 10h, 00h, 03h, 06h, 00h, 06h, 02h, 10h
	db	 04h, 45h, 45h, 45h, 05h, 05h, 05h, 05h
	db	 05h, 35h, 30h, 00h, 50h, 00h, 00h, 00h
	db	 00h, 20h, 28h, 38h, 50h, 58h, 07h, 08h
	db	 00h, 37h, 30h, 30h, 57h, 50h, 07h, 00h
	db	 00h, 20h, 20h, 08h, 00h, 00h, 00h, 00h
	db	 08h, 60h, 60h, 60h, 60h, 60h, 60h, 00h
	db	 00h, 70h, 78h, 78h, 78h, 78h, 78h, 08h
	db	 07h, 08h, 00h, 00h, 07h, 00h, 08h, 08h
	db	 08h, 00h, 00h, 08h, 00h, 08h, 00h, 00h
	db	 08h

formchar	db 'bcdefginopsuxEGX'
nullstring	db '(null)',0
output_flush	p? ?

OPST_table	label size_t
	dw	OPST_normal
	dw	OPST_percent
	dw	OPST_flag
	dw	OPST_width
	dw	OPST_dot
	dw	OPST_precision
	dw	OPST_size
	dw	OPST_type

output_proctab	label size_t
	dw	OUTPUT_b
	dw	OUTPUT_c
	dw	OUTPUT_d
	dw	OUTPUT_dummy
	dw	OUTPUT_dummy
	dw	OUTPUT_dummy
	dw	OUTPUT_d
	dw	OUTPUT_n
	dw	OUTPUT_o
	dw	OUTPUT_p
	dw	OUTPUT_s
	dw	OUTPUT_u
	dw	OUTPUT_x
	dw	OUTPUT_dummy
	dw	OUTPUT_dummy
	dw	OUTPUT_xu

S_OUTPUT	STRUC
OP_filep	dd ?
OP_format	dd ?
OP_charsout	dw ?
OP_hexoff	dw ?
OP_state	dw ?
OP_curadix	dw ?
OP_prefix	db 2 dup(?)
OP_count	dw ?
OP_prefixlen	dw ?
OP_no_output	dw ?
OP_fldwidth	dw ?
OP_padding	dw ?
OP_text		dd ?
OP_capitalize	dw ?
OP_number	dd ?
OP_ddtemp	dd ?
OP_dwtemp	dw ?
OP_buffer	db BUFFERSIZE dup(?)
OP_STACK	dd ? ; [(E)BP]
ifndef __c__
OP_CSIP		dw ?
endif
ifdef __CDECL__
OP_ARGfile	dd ?
OP_ARGformat	dd ?
OP_argp		dd ?
else
OP_argp		dd ?
OP_ARGformat	dd ?
OP_ARGfile	dd ?
endif
S_OUTPUT	ENDS

	.code

OPST_normal:
	mov	al,dl

OUTPUT_PUTC:
	les	bx,[bp].S_OUTPUT.OP_filep
	dec	es:[bx].S_FILE.iob_cnt
	jl	OPPUTC_00
	inc	WORD PTR es:[bx].S_FILE.iob_bp
	les	bx,es:[bx].S_FILE.iob_bp
	mov	es:[bx-1],al
    OPPUTC_01:
	inc	[bp].S_OUTPUT.OP_charsout
	ret
    OPPUTC_00:
      ifdef __CDECL__
	pushm	[bp].S_OUTPUT.OP_filep
	push	ax
      else
	push	ax
	pushm	[bp].S_OUTPUT.OP_filep
      endif
	call	output_flush
	cmp	ax,-1
	jne	OPPUTC_01
	mov	[bp].S_OUTPUT.OP_charsout,ax
	ret

output_getd:	; Get DWORD from stack
	lea	bx,[bp].S_OUTPUT.OP_argp
	mov	ax,[bx+2]
	add	WORD PTR [bx],4
	mov	bx,[bx]
	mov	es,ax
ifdef __3__
	mov	eax,es:[bx-4]
else
	mov	ax,es:[bx-4]
	mov	dx,es:[bx-2]
endif
	ret

output_getw:	; Get WORD from stack
	lea	bx,[bp].S_OUTPUT.OP_argp
	mov	ax,[bx+2]
	add	WORD PTR [bx],2
	mov	bx,[bx]
	mov	es,ax
	mov	ax,es:[bx-2]
	ret

OPST_percent:
	sub	ax,ax
	mov	[bp].S_OUTPUT.OP_no_output,ax
	mov	[bp].S_OUTPUT.OP_fldwidth,ax
	mov	[bp].S_OUTPUT.OP_prefixlen,ax
	mov	[bp].S_OUTPUT.OP_capitalize,ax
	mov	si,ax	; bufferiswide (default)
	mov	di,ax	; precision
	dec	di
	ret

OPST_flag:
	mov al,dl
	.if al == '+'
	    or si,FLAG_SIGN	; '+' force sign indicator
	.elseif al == ' '
	    or si,FLAG_SIGNSP	; ' ' force sign or space
	.elseif al == '#'
	    or si,FLAG_ALTERNATE	; '#' alternate form
	.elseif al == '-'
	    or si,FLAG_LEFT		; '-' left justify
	.elseif al == '0'
	    or si,FLAG_LEADZERO ; '0' pad with leading zeros
	.endif
	ret

OPST_width:
	.if dl == '*'
	    call output_getw
	    mov [bp].S_OUTPUT.OP_fldwidth,ax
	    cmp ax,0
	    jge @F
	    or	si,4
	    neg ax
	    mov [bp].S_OUTPUT.OP_fldwidth,ax
	  @@:
	.else
	    mov al,dl
	    cbw
	    push ax
	    mov	 ax,[bp].S_OUTPUT.OP_fldwidth
	    mov	 dx,10
	    imul dx
	    pop	 dx
	    add	 dx,ax
	    add	 dx,-48
	    mov	 [bp].S_OUTPUT.OP_fldwidth,dx
	.endif
	ret

OPST_dot:
	sub di,di
	ret

OPST_precision:
	.if dl == '*'
	    call output_getw
	    mov di,ax
	    cmp ax,0
	    jge @F
	    mov di,-1
	.else
	    mov al,dl
	    cbw
	    push ax
	    mov	 ax,di
	    mov	 dx,10
	    imul dx
	    pop	 dx
	    add	 dx,ax
	    add	 dx,-48
	    mov	 di,dx
	.endif
      @@:
	ret

OPST_size:
	.if dl == 'l'
	    or si,FLAG_LONG
	.endif
	ret

OPST_type:
	sub bx,bx
	mov cx,16
	.repeat
	    .if dl == formchar[bx]
		shl bx,1
		call output_proctab[bx]
		.break
	    .endif
	    inc bx
	.untilcxz
	call OUTPUT
	ret

OUTPUT_b:
	push	si
	call	output_getw
	test	si,FLAG_LONG
	mov	si,16
	jnz	OUTPB_00
	mov	si,8
    OUTPB_00:
	mov	[bp].S_OUTPUT.OP_count,si
	mov	dx,ax
    OUTPB_02:
	sub	ax,ax
	shr	dx,1
	adc	al,'0'
	dec	si
	mov	[bp].S_OUTPUT.OP_buffer[si],al
	jnz	OUTPB_02
	pop	si
	jmp	OUTPUT_LDTEXT

OUTPUT_c:
	call	output_getw
	mov	dx,ax
	mov	[bp].S_OUTPUT.OP_buffer,al
	mov	[bp].S_OUTPUT.OP_count,1

OUTPUT_LDTEXT:
	lea	ax,[bp].S_OUTPUT.OP_buffer
	mov	WORD PTR [bp].S_OUTPUT.OP_text+2,ss
	mov	WORD PTR [bp].S_OUTPUT.OP_text,ax
	ret

OUTPUT_s:
	.if di == -1
	    mov cx,7FFFh
	.else
	    mov cx,di
	.endif
	call	output_getd
ifdef __16__
	mov	WORD PTR [bp].S_OUTPUT.OP_text+2,dx
	mov	WORD PTR [bp].S_OUTPUT.OP_text,ax
	or	ax,dx
else
	mov	[bp].S_OUTPUT.OP_text,eax
	test	eax,eax
endif
	jnz	OUTPS_02
    OUTPS_NULL:
	mov	WORD PTR [bp].S_OUTPUT.OP_text+2,ds
	mov	WORD PTR [bp].S_OUTPUT.OP_text,offset nullstring
    OUTPS_02:
	les	bx,[bp].S_OUTPUT.OP_text
    OUTPS_03:
	cmp	BYTE PTR es:[bx],0
	je	OUTPS_04
	inc	bx
	dec	cx
	jnz	OUTPS_03
    OUTPS_04:
	sub	bx,WORD PTR [bp].S_OUTPUT.OP_text
	mov	[bp].S_OUTPUT.OP_count,bx
	ret

OUTPUT_n:
	call	output_getd
	les	bx,es:[bx]-4
	test	si,FLAG_LONG
	jnz	@F
	mov	ax,[bp].S_OUTPUT.OP_charsout
	mov	es:[bx],ax
	ret
      @@:
	mov	ax,[bp].S_OUTPUT.OP_charsout
	mov	es:[bx],ax
	mov	[bp].S_OUTPUT.OP_no_output,1
	ret

OUTPUT_p:
	mov	di,8
	or	si,FLAG_LONG

OUTPUT_xu:
	mov	[bp].S_OUTPUT.OP_hexoff,'A'-'9'-1
	jmp	OPCOMMONHEX

OUTPUT_x:
	mov	[bp].S_OUTPUT.OP_hexoff,'a'-'9'-1

OPCOMMONHEX:
	mov	[bp].S_OUTPUT.OP_curadix,16
	test	si,FLAG_ALTERNATE
	jz	@F
	mov	[bp].S_OUTPUT.OP_prefix,'0'
	mov	[bp].S_OUTPUT.OP_prefix+1,'x'
	mov	[bp].S_OUTPUT.OP_prefixlen,2
      @@:
	test	si,FLAG_LONG
	jnz	OUTPUT_LONGINT
	cmp	[bp].S_OUTPUT.OP_fldwidth,2
	jne	OUTPUT_SHORTINT
	call	output_getw
	and	ax,00FFh
	jmp	OUTPUT_UNSIGNED

OUTPUT_o:
	mov	[bp].S_OUTPUT.OP_curadix,8
	test	si,FLAG_ALTERNATE
	jz	OUTPUT_GENINT
	or	si,FLAG_FORCEOCTAL
	jmp	OUTPUT_GENINT

OUTPUT_d:
	or	si,FLAG_SIGNED

OUTPUT_u:
	mov	[bp].S_OUTPUT.OP_curadix,10

OUTPUT_GENINT:
	test	si,FLAG_LONG
	jz	OUTPUT_SHORTINT

OUTPUT_LONGINT:
	call	output_getd
	jmp	OUTPUT_NUMBER

OUTPUT_SHORTINT:
	call	output_getw
	test	si,FLAG_SIGNED
	jz	OUTPUT_UNSIGNED
ifdef __3__
	movsx eax,ax
else
	cwd
endif
	jmp	OUTPUT_NUMBER

OUTPUT_UNSIGNED:
ifdef __3__
	movzx eax,ax
else
	xor dx,dx
endif

OUTPUT_NUMBER:
ifdef __3__
	mov	[bp].S_OUTPUT.OP_ddtemp,eax
	test	si,FLAG_SIGNED
	jz	@F
	cmp	eax,0
	jnl	@F
	neg	eax
	or	si,FLAG_NEGATIVE
      @@:
	mov	[bp].S_OUTPUT.OP_number,eax
else
	stom	[bp].S_OUTPUT.OP_ddtemp
	test	si,FLAG_SIGNED
	jz	@F
	test	dx,dx
	jns	@F
	neg	ax
	neg	dx
	sbb	dx,0
	or	si,FLAG_NEGATIVE
      @@:
	stom	[bp].S_OUTPUT.OP_number
endif
	test	di,di
	jnl	OPNUM_01
	mov	di,1
	jmp	OPNUM_02
    OPNUM_01:
	and	si,-9
    OPNUM_02:
ifdef __3__
	test	eax,eax
else
	test	ax,ax
	jnz	OPNUM_03
	test	dx,dx
endif
	jnz	OPNUM_03
	mov	[bp].S_OUTPUT.OP_prefixlen,ax
    OPNUM_03:
	lea	ax,[bp].S_OUTPUT.OP_buffer+512-1
	mov	WORD PTR [bp].S_OUTPUT.OP_text+2,ss
	mov	WORD PTR [bp].S_OUTPUT.OP_text,ax
	jmp	OPNUM_06
    OPNUM_04:
ifdef __16__
	mov	bx,[bp].S_OUTPUT.OP_curadix
	xor	cx,cx
	lodm	[bp].S_OUTPUT.OP_number
	call	_div32
	stom	[bp].S_OUTPUT.OP_number
	add	bx,'0'
	mov	cx,bx
else
	movzx	ebx,[bp].S_OUTPUT.OP_curadix
	mov	eax,[bp].S_OUTPUT.OP_number
	sub	edx,edx
	div	ebx
	mov	[bp].S_OUTPUT.OP_number,eax
	add	dx,'0'
	mov	cx,dx
endif
	cmp	cx,'9'
	jng	OPNUM_05
	add	cx,[bp].S_OUTPUT.OP_hexoff
    OPNUM_05:
	les	bx,[bp].S_OUTPUT.OP_text
	mov	es:[bx],cl
	dec	WORD PTR [bp].S_OUTPUT.OP_text
    OPNUM_06:
	mov	cx,di
	dec	di
	test	cx,cx
	jg	OPNUM_04
ifdef __3__
	test	eax,eax
else
	or	ax,dx
endif
	jnz	OPNUM_04
	lea	ax,[bp].S_OUTPUT.OP_buffer+512-1
	sub	ax,WORD PTR [bp].S_OUTPUT.OP_text
	mov	[bp].S_OUTPUT.OP_count,ax
	inc	WORD PTR [bp].S_OUTPUT.OP_text
	test	si,FLAG_FORCEOCTAL
	jz	OUTPUT_dummy
	les	bx,[bp].S_OUTPUT.OP_text
	cmp	BYTE PTR es:[bx],'0'
	jne	OPNUM_07
	cmp	[bp].S_OUTPUT.OP_count,0
	jne	OUTPUT_dummy
    OPNUM_07:
	dec	bx
	mov	WORD PTR [bp].S_OUTPUT.OP_text,bx
	mov	BYTE PTR es:[bx],'0'
	inc	[bp].S_OUTPUT.OP_count
OUTPUT_dummy:
	ret

OUTPUT_MULTI:
	push	si
	push	di
	sub	ah,ah
	mov	si,ax
	mov	di,dx
	jmp	OPMULTI_01
    OPMULTI_00:
	mov	ax,si
	call	OUTPUT_PUTC
	cmp	[bp].S_OUTPUT.OP_charsout,-1
	je	OPMULTI_02
    OPMULTI_01:
	mov	ax,di
	dec	di
	test	ax,ax
	jg OPMULTI_00
    OPMULTI_02:
	pop	di
	pop	si
	ret

OUTPUT_STRING:
	push	di
	push	si
	mov	di,ax
	mov	si,cx
	mov	bx,dx
	jmp	OPSTR_01
    OPSTR_00:
	mov	es,di
	mov	al,es:[bx]
	inc	bx
	push	bx
	call	OUTPUT_PUTC
	pop	bx
	cmp	[bp].S_OUTPUT.OP_charsout,-1
	jz	OPSTR_02
    OPSTR_01:
	mov	ax,si
	dec	si
	or	ax,ax
	jg	OPSTR_00
    OPSTR_02:
	pop	si
	pop	di
	ret

OUTPUT:
	sub	ax,ax
	cmp	ax,[bp].S_OUTPUT.OP_no_output
	je	OUTPUT_00
	ret
    OUTPUT_00:
	test	si,FLAG_SIGNED
	jz	OUTPUT_03
	test	si,FLAG_NEGATIVE
	jz	OUTPUT_01
	mov	[bp].S_OUTPUT.OP_prefix,'-'
	mov	[bp].S_OUTPUT.OP_prefixlen,1
	jmp	OUTPUT_03
    OUTPUT_01:
	test	si,FLAG_SIGN
	jz	OUTPUT_02
	mov	[bp].S_OUTPUT.OP_prefix,43
	mov	[bp].S_OUTPUT.OP_prefixlen,1
	jmp	OUTPUT_03
    OUTPUT_02:
	test	si,FLAG_SIGNSP
	jz	OUTPUT_03
	mov	[bp].S_OUTPUT.OP_prefix,' '
	mov	[bp].S_OUTPUT.OP_prefixlen,1
    OUTPUT_03:
	mov	ax,[bp].S_OUTPUT.OP_fldwidth
	sub	ax,[bp].S_OUTPUT.OP_count
	sub	ax,[bp].S_OUTPUT.OP_prefixlen
	mov	[bp].S_OUTPUT.OP_padding,ax
	test	si,FLAG_LEFT or FLAG_LEADZERO
	jnz	OUTPUT_04
	mov	dx,ax
	mov	ax,' '
	call	OUTPUT_MULTI
    OUTPUT_04:
	mov	ax,ss
	lea	dx,[bp].S_OUTPUT.OP_prefix
	mov	cx,[bp].S_OUTPUT.OP_prefixlen
	call	OUTPUT_STRING
	test	si,FLAG_LEADZERO
	jz	OUTPUT_05
	test	si,FLAG_LEFT
	jnz	OUTPUT_05
	mov	ax,'0'
	mov	dx,[bp].S_OUTPUT.OP_padding
	call	OUTPUT_MULTI
    OUTPUT_05:
	cmp	[bp].S_OUTPUT.OP_count,0
	jng	OUTPUT_08
	movmx	[bp].S_OUTPUT.OP_ddtemp,[bp].S_OUTPUT.OP_text
	mov	ax,[bp].S_OUTPUT.OP_count
	mov	[bp].S_OUTPUT.OP_dwtemp,ax
	jmp	OUTPUT_07
    OUTPUT_06:
	les	bx,[bp].S_OUTPUT.OP_ddtemp
	inc	WORD PTR [bp].S_OUTPUT.OP_ddtemp
	mov	al,es:[bx]
	call	OUTPUT_PUTC
    OUTPUT_07:
	mov	ax,[bp].S_OUTPUT.OP_dwtemp
	dec	[bp].S_OUTPUT.OP_dwtemp
	or	ax,ax
	jg	OUTPUT_06
	jmp	OUTPUT_09
    OUTPUT_08:
	mov	ax,WORD PTR [bp].S_OUTPUT.OP_text+2
	mov	dx,WORD PTR [bp].S_OUTPUT.OP_text
	mov	cx,[bp].S_OUTPUT.OP_count
	call	OUTPUT_STRING
    OUTPUT_09:
	test	si,FLAG_LEFT
	jz	OUTPUT_10
	mov	ax,' '
	mov	dx,[bp].S_OUTPUT.OP_padding
	call	OUTPUT_MULTI
    OUTPUT_10:
	ret

_output PROC _CType PUBLIC USES dx cx bx si di bp filep:DWORD,
	format:DWORD, argp:DWORD
local	OP[S_OUTPUT.OP_STACK]:BYTE
	lea bp,OP
	movmx [bp].S_OUTPUT.OP_format,[bp].S_OUTPUT.OP_ARGformat
	movmx [bp].S_OUTPUT.OP_filep,[bp].S_OUTPUT.OP_ARGfile
	sub ax,ax
	mov [bp].S_OUTPUT.OP_count,ax
	mov [bp].S_OUTPUT.OP_charsout,ax
	mov [bp].S_OUTPUT.OP_state,ax
	.repeat
	    les bx,[bp].S_OUTPUT.OP_format
ifdef __16__
	    inc WORD PTR [bp].S_OUTPUT.OP_format
else
	    inc [bp].S_OUTPUT.OP_format
endif
	    mov al,es:[bx]
	    mov ah,0
	    mov dx,ax
	    .break .if !al
	    .break .if [bp].S_OUTPUT.OP_charsout > 7FFFh
	    .if al < ' ' || al > 'x'
		sub ax,ax
	    .else
		mov bx,ax
		mov al,cl_table[bx-32]
		and ax,15
	    .endif
	    mov cx,ax
	    mov bx,ax
	    shl bx,3
	    add bx,[bp].S_OUTPUT.OP_state
	    mov al,cl_table[bx]
	    shr ax,4
	    mov [bp].S_OUTPUT.OP_state,ax
	    mov bx,ax
	    .if ax <= 7
		add bx,bx
		call OPST_table[bx]
	    .endif
	.until 0
	mov ax,[bp].S_OUTPUT.OP_charsout
	ret
_output ENDP

	END
