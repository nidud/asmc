; EMMINIT.ASM--
; Copyright (C) 2015 Doszip Developers
include alloc.inc

PUBLIC	dzemm

.data
emmstate	db 0
dzemm		db 0

.code

emmversion PROC _CType PUBLIC
	sub ax,ax
	.if emmstate != al
	    mov ah,46h
	    int 67h
	    .if ah
		sub ax,ax
	    .endif
	.endif
	ret
emmversion ENDP

emminit:
	mov	ah,35h
	mov	al,67h
	int	21h
	mov	bx,10
	mov	ax,es:[bx]
	cmp	ax,'ME'
	jne	@F
	mov	ax,es:[bx+2]
	cmp	ax,'XM'
	jne	@F
	mov	ah,46h		; get EMM version
	int	67h
	test	ah,ah
	jnz	@F
	cmp	al,40h		; 4.0
	jb	@F
	inc	emmstate
	mov	ax,4000h	; get DZEMM state
	int	67h		; return AX = 0001
	dec	ax
	jnz	@F
	inc	dzemm
      @@:
	ret

pragma_init emminit, 6

	END
