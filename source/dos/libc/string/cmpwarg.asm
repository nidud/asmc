; CMPWARG.ASM--
; Copyright (C) 2015 Doszip Developers

include string.inc

	.code

cmpwarg PROC _CType PUBLIC USES si di filep:PTR BYTE, maskp:PTR BYTE
	push	ds
	lds	si,filep
	les	di,maskp
	xor	ax,ax
    cmpwarg_next:
	mov	al,[si]
	mov	ah,es:[di]
	inc	si
	inc	di
	cmp	ah,'*'
	je	cmpwarg_star
	test	al,al
	jz	cmpwarg_zero
	test	ah,ah
	jz	cmpwarg_zero
	cmp	ah,'?'
	je	cmpwarg_next
	cmp	ah,'.'
	je	cmpwarg_04
	cmp	al,'.'
	je	cmpwarg_fail
	or	ax,2020h
	cmp	ah,al
	je	cmpwarg_next
	jmp	cmpwarg_fail
    cmpwarg_zero:
	test	ax,ax
	jnz	cmpwarg_fail
    cmpwarg_ok:
	mov	ax,1
    cmpwarg_end:
	test	ax,ax
	pop	ds
	ret
    cmpwarg_04:
	cmp	al,'.'
	je	cmpwarg_next
    cmpwarg_fail:
	xor	ax,ax
	jmp	cmpwarg_end
    cmpwarg_star:
	mov	ah,es:[di]
	test	ah,ah
	jz	cmpwarg_ok	; find '.' --> '*' | '*abc' | '*.txt'
	inc	di
	cmp	ah,'.'
	jne	cmpwarg_star
	xor	dx,dx		; found
    cmpwarg_type:
	test	al,al
	jz	cmpwarg_test
	cmp	al,ah
	je	cmpwarg_dxsi
    cmpwarg_lods:
	mov	al,[si]
	inc	si
	jmp	cmpwarg_type
    cmpwarg_dxsi:
	mov	dx,si
	jmp	cmpwarg_lods
    cmpwarg_test:
	test	dx,dx
	mov	si,dx
	jnz	cmpwarg_next
	mov	ah,es:[di]
	inc	di
	cmp	ah,'*'
	je	cmpwarg_star
	jmp	cmpwarg_zero
cmpwarg ENDP

	END
