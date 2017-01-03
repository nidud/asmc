; TOGETBIT.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

togetbitflag PROC _CType PUBLIC USES si di bx tobj:DWORD, count:size_t, flag:size_t
	mov	si,flag
	mov	dx,count
	dec	dx
	mov	ax,dx
	shl	ax,4
	les	bx,tobj
	add	bx,ax
	xor	ax,ax
	mov	di,ax
    togetbitflag_loop:
	mov	cx,es:[bx]
	sub	bx,16
	and	cx,si
	jz	@F
	or	al,1
      @@:
	shl	di,1
	shl	ax,1
	adc	di,0
	dec	dx
	or	dx,dx
	jg	togetbitflag_loop
	mov	cx,es:[bx]
	and	cx,si
	jz	@F
	or	al,1
      @@:
	mov	dx,di
	ret
togetbitflag ENDP

	END
