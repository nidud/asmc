; RCOPEN.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

rcopen	PROC _CType PUBLIC rect:DWORD,flag:WORD,attrib:WORD,ttl:DWORD,wp:DWORD
	test	flag,_D_MYBUF
	jnz	@F
	invoke	rcalloc,rect,flag
	stom	wp
	jnz	@F
	jmp	rcopen_end
      @@:
	invoke	rcread,rect,wp
	mov	dx,flag
	and	dx,_D_CLEAR or _D_BACKG or _D_FOREG
	jz	rcopen_end
	mov	al,rect.S_RECT.rc_row
	mov	ah,0
	mul	rect.S_RECT.rc_col
	mov	cx,attrib
	cmp	dx,_D_CLEAR
	je	rcopen_clear
	cmp	dx,_D_COLOR
	je	rcopen_color
	cmp	dx,_D_BACKG
	je	rcopen_background
	cmp	dx,_D_FOREG
	je	rcopen_foreground
	mov	ch,cl
	mov	cl,' '
	invoke	wcputw,wp,ax,cx
	jmp	rcopen_title
    rcopen_clear:
	invoke	wcputw,wp,ax,' '
	jmp	rcopen_title
    rcopen_color:
	invoke	wcputa,wp,ax,cx
	jmp	rcopen_title
    rcopen_background:
	invoke	wcputbg,wp,ax,cx
	jmp	rcopen_title
    rcopen_foreground:
	invoke	wcputfg,wp,ax,cx
    rcopen_title:
	sub	ax,ax
	cmp	WORD PTR ttl,ax
	jz	rcopen_end
	mov	al,rect.S_RECT.rc_col
	invoke	wctitle,wp,ax,ttl
    rcopen_end:
	lodm	wp
	test	ax,ax
	ret
rcopen	ENDP

	END
