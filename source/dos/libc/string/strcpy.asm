; STRCPY.ASM--
; Copyright (C) 2015 Doszip Developers

include string.inc

	.code

strcpy	PROC _CType PUBLIC USES si di s1:PTR BYTE, s2:PTR BYTE
	push	ds
	cld?
	sub	al,al
	mov	cx,-1
	les	di,s2
	repne	scasb
	les	di,s1
	lds	si,s2
	mov	ax,di
	not	cx
	shr	cx,1
	rep	movsw
	jc	strcpy_mov
    strcpy_end:
	mov	dx,WORD PTR s1+2
	pop	ds
	ret
    strcpy_mov:
	movsb
	jmp strcpy_end
strcpy	ENDP

	END
