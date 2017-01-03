; OUNGETC.ASM--
; Copyright (C) 2015 Doszip Developers

include iost.inc
include io.inc
ifdef __TE__
tiofread PROTO
endif

	.code

oungetc PROC _CType PUBLIC USES si di
	mov	si,offset STDI
	xor	ax,ax
	cmp	ax,[si].S_IOST.ios_i
	je	oungetc_02
    oungetc_00:
	dec	[si].S_IOST.ios_i
	mov	ax,[si].S_IOST.ios_i
	les	di,[si].S_IOST.ios_bp
	add	di,ax
	inc	ax		; es:0 and ax 0 = ZF set
	mov	ah,0
	mov	al,es:[di]
    oungetc_01:
	ret
    oungetc_02:
  ifdef __MEMVIEW__
	test	[si].S_IOST.ios_flag,IO_MEMREAD
	jnz	oungetc_10
  endif
  ifdef __TE__
	test	[si].S_IOST.ios_flag,IO_LINEBUF
	jnz	oungetc_lb
  endif
	invoke	lseek,[si].S_IOST.ios_file,0,SEEK_CUR
	cmp	dx,-1
	jne	oungetc_03
	cmp	ax,-1
	je	oungetc_eof	; current offset to DX:AX
    oungetc_03:
	mov	cx,[si].S_IOST.ios_c	; last read size to CX
	test	dx,dx		; >= current offset ?
	jnz	oungetc_04
	cmp	cx,ax
	ja	oungetc_error	; stream not align if above
	je	oungetc_eof	; EOF == top of file
	cmp	ax,[si].S_IOST.ios_size
	jne	oungetc_04
	cmp	dx,WORD PTR [si].S_IOST.ios_offset
	jne	oungetc_04
	cmp	dx,WORD PTR [si].S_IOST.ios_offset[2]
	je	oungetc_eof
    oungetc_04:
	sub	ax,cx		; adjust offset to start
	sbb	dx,0
	mov	cx,[si].S_IOST.ios_size
	jnz	oungetc_05
	cmp	cx,ax
	jae	oungetc_07
   oungetc_05:
	sub	ax,cx
	sbb	dx,0
   oungetc_06:
	push	cx
	invoke	oseek,dx::ax,SEEK_SET
	pop	ax
	jz	oungetc_eof
	cmp	ax,[si].S_IOST.ios_c
	ja	oungetc_error
	mov	[si].S_IOST.ios_c,ax
	mov	[si].S_IOST.ios_i,ax
	jmp	oungetc_00
    oungetc_07:
	mov	cx,ax
	xor	ax,ax
	mov	dx,ax
	jmp	oungetc_06
    oungetc_error:
	or	[si].S_IOST.ios_flag,IO_ERROR
    oungetc_eof:
	mov	ax,-1
	xor	si,si
	jmp	oungetc_01
  ifdef __MEMVIEW__
    oungetc_10:
	lodm	[si].S_IOST.ios_offset
	add	ax,[si].S_IOST.ios_c
	adc	dx,0
	jmp	oungetc_03
  endif
  ifdef __TE__
    oungetc_lb:
	cmp	[si].S_IOST.ios_l,ax	; first line ?
	je	oungetc_eof
	inc	[si].S_IOST.ios_c
	sub	[si].S_IOST.ios_l,2
	call	tiofread
	jz	oungetc_eof
	mov	ax,[si].S_IOST.ios_c
	mov	[si].S_IOST.ios_i,ax
	jmp	oungetc_00
  endif
oungetc ENDP

	END
