; WCZIP.ASM--
; Copyright (C) 2015 Doszip Developers
include conio.inc

	.code

compress:
	lodsb
	mov	dl,al
	mov	dh,al
	and	dh,0F0h
	cmp	al,[si]
	jnz	compress_01
	mov	bx,0F001h
	jmp	compress_04
    compress_01:
	cmp	dh,0F0h
	jnz	compress_08
	mov	ax,01F0h
	jmp	compress_07
	mov	al,dl
	stosb
	jmp	compress_08
    compress_03:
	inc	bx
	lodsb
	cmp	al,[si]
	jne	compress_05
    compress_04:
	dec	cx
	jnz	compress_03
    compress_05:
	mov	ax,bx
	cmp	bx,0F002h
	jnz	compress_06
	cmp	dh,0F0h
	jz	compress_06
	mov	al,dl
	stosb
	jmp	compress_08
    compress_06:
	xchg	ah,al
    compress_07:
	stosw
	mov	al,dl
    compress_08:
	stosb
	test	cx,cx
	jz	compress_09
	dec	cx
	jnz	compress
    compress_09:
	ret

wczip	PROC _CType PUBLIC USES si di bx dest:DWORD, src:DWORD, count:size_t
	push	ds
	cld?
	mov	cx,count
	les	di,dest
	lds	si,src
	add	di,3
	mov	bx,di
	add	bx,cx
      @@:
	lodsw
	xchg	al,ah
	mov	es:[bx],ah
	stosb
	inc	bx
	dec	cx
	jnz	@B
	lds	si,dest
	mov	di,si
	add	si,3
	mov	cx,count
	call	compress
	mov	cx,count
	call	compress
	mov	ax,di
	sub	ax,WORD PTR dest
	shr	ax,1
	inc	ax
	pop	ds
	ret
wczip	ENDP

	END
