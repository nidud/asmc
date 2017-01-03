; GETENVP.ASM--
; Copyright (C) 2015 Doszip Developers

include stdlib.inc
include string.inc

extrn	envseg:WORD

	.code

getenvp PROC _CType PUBLIC USES si di bx enval:PTR BYTE
	push	ds
	mov	es,envseg
	lds	si,enval
	mov	al,[si]
	call	ftolower
	mov	bl,al
	mov	cx,7FFFh
	xor	ax,ax
	mov	di,ax
	cld
    getenvp_00:
	mov	al,es:[di]
	call	ftolower
	cmp	al,bl
	je	getenvp_02
    getenvp_01:
	mov	al,0
	repnz	scasb
	test	cx,cx
	jz	getenvp_null
	cmp	es:[di],al
	jne	getenvp_00
	jmp	getenvp_null
    getenvp_02:
	push	cx
	call	strcmpi
	mov	si,cx
	pop	cx
	jz	getenvp_03
	cmp	ah,'%'
	je	getenvp_04
    getenvp_03:
	cmp	ax,'='
	je	getenvp_04
	mov	si,dx
	mov	al,[si]
	call	ftolower
	mov	bl,al
	jmp	getenvp_01
    getenvp_04:
	mov	di,si
	cmp	al,'='
	jne	getenvp_01
	inc	di
	mov	ax,di
	mov	dx,es
	jmp	getenvp_end
    getenvp_null:
	xor	ax,ax
	cwd
    getenvp_end:
	pop	ds
	ret
getenvp ENDP

	END
