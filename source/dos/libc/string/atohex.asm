; ATOHEX.ASM--
; Copyright (C) 2015 Doszip Developers

include string.inc

	.code

atohex PROC _CType PUBLIC USES si di string:PTR BYTE
	mov	di,WORD PTR string
	invoke	strlen,string
	test	ax,ax
	jz	atohex_end
	cmp	ax,64
	jnb	atohex_end
	dec	ax
	mov	si,di
	add	si,ax
	add	ax,ax
	add	di,ax
	mov	BYTE PTR es:[di][2],0
    atohex_loop:
	mov	al,es:[si]
	mov	ah,al
	shr	al,4
	and	ah,15
	add	ax,'00'
	cmp	al,'9'
	jbe	atohex_01
	add	al,7
    atohex_01:
	cmp	ah,'9'
	jbe	atohex_02
	add	ah,7
    atohex_02:
	mov	es:[di],ax
	dec	si
	sub	di,2
	cmp	di,si
	jae	atohex_loop
    atohex_end:
	lodm	string
	ret
atohex ENDP

	END
