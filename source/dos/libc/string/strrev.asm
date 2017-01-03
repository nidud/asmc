; STRREV.ASM--
; Copyright (C) 2015 Doszip Developers

include string.inc

	.code

strrev	PROC _CType PUBLIC USES cx si di string:PTR BYTE
	push	ds
	cld?
	lds	si,string
	les	di,string
	mov	al,0
	mov	cx,-1
	repnz	scasb
	cmp	cx,-2
	je	strrev_02
	sub	di,2
	xchg	si,di
	jmp	strrev_01
    strrev_00:
	mov	al,[di]
	movsb
	mov	[si-1],al
	sub	si,2
    strrev_01:
	cmp	di,si
	jc	strrev_00
    strrev_02:
	lodm	string
	pop	ds
	ret
strrev	ENDP

	END
