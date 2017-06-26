; GETENVAL.ASM--
; Copyright (C) 2015 Doszip Developers

include stdlib.inc
include string.inc

extrn	envseg:WORD

	.code

getenval PROC _CType PUBLIC USES si di result:PTR BYTE, enval:PTR BYTE
	mov	es,envseg
	push	ds
	lds	si,enval
	mov	al,[si]
	call	ftolower
	mov	bl,al
	mov	cx,7FFFh
	xor	ax,ax
	mov	di,ax
	cld?
    getenval_00:
	mov	al,es:[di]
	call	ftolower
	cmp	al,bl
	je	getenval_02
    getenval_01:
	mov	al,0
	repnz	scasb
	test	cx,cx
	jz	getenval_07
	cmp	es:[di],al
	jne	getenval_00
	jmp	getenval_07
    getenval_02:
	push	cx
	call	strcmpi
	mov	si,cx
	pop	cx
	jz	getenval_03
	cmp	ah,'%'
	je	getenval_04
    getenval_03:
	mov	si,dx
	mov	al,[si]
	call	ftolower
	mov	bl,al
	jmp	getenval_01
    getenval_04:
	mov	di,si
	cmp	al,'='
	jne	getenval_01
	inc	di
	lds	si,result
    getenval_05:
	mov	al,es:[di]
	mov	[si],al
	test	al,al
	jz	getenval_06
	inc	si
	inc	di
	jmp	getenval_05
    getenval_06:
	mov	ax,WORD PTR result
	mov	dx,WORD PTR result+2
	jmp	getenval_08
    getenval_07:
	xor	ax,ax
	cwd
    getenval_08:
	pop	ds
	ret
getenval ENDP

	END
