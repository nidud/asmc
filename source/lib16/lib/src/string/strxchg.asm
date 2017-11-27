; STRXCHG.ASM--
; Copyright (C) 2015 Doszip Developers

include string.inc
include dir.inc

	.code

strxchg PROC _CType PUBLIC USES si di strb:PTR BYTE, ostr:PTR BYTE, nstr:PTR BYTE, olen:size_t
local convb[1024]:BYTE
	push	ds
    strxchg_00:
	les	di,strb
	lds	si,ostr
	sub	al,al
	cmp	al,[si]
	je	strxchg_03
    strxchg_01:
	mov	al,[si]
	mov	ah,al
	sub	al,'A'
	cmp	al,'Z' - 'A' + 1
	sbb	al,al
	and	al,'a' - 'A'
	xor	ah,al
    strxchg_02:
	mov	al,es:[di]
	test	al,al
	jz	strxchg_03
	mov	dl,al
	sub	al,'A'
	cmp	al,'Z' - 'A' + 1
	sbb	al,al
	and	al,'a' - 'A'
	xor	dl,al
	mov	al,dl
	inc	di
	cmp	al,ah
	jne	strxchg_02
	inc	si
	call	strcmpi
	mov	si,WORD PTR ostr
	jnz	strxchg_01
	mov	dx,es
	mov	ax,di
	dec	ax
	jmp	strxchg_04
    strxchg_03:
	sub	ax,ax
	mov	dx,es
	mov	ax,WORD PTR strb
    strxchg_04:
	jnz	strxchg_05
	pop	ds
	ret
    strxchg_05:
	mov	si,ax
	mov	BYTE PTR [si],0
	invoke	strcpy,addr convb,strb
	invoke	strcat,dx::ax,nstr
	add	si,olen
	mov	cx,WORD PTR strb+2
	invoke	strcat,dx::ax,cx::si
	mov	si,ax
	add	si,WMAXPATH-1
	mov	BYTE PTR [si],0
	invoke	strcpy,strb,dx::ax
	jmp	strxchg_00
strxchg ENDP

	END
