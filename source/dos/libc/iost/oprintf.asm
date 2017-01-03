; OPRINTF.ASM--
; Copyright (C) 2015 Doszip Developers

include stdio.inc
include iost.inc

	.code

oprintf PROC _CDecl PUBLIC USES si format:DWORD, argptr:VARARG
	invoke	ftobufin,format,addr argptr
	mov	cx,ax
	mov	si,offset _bufin
	jmp	while_1
    lf:
	mov	ax,0Dh
	invoke	oputc
	jz	break
	inc	cx
	mov	ax,0Ah
	jmp	continue
    while_1:
	mov	al,[si]
	inc	si
	test	al,al
	jz	break
	cmp	al,0Ah
	je	lf
    continue:
	invoke	oputc
	jnz	while_1
    break:
	mov	ax,cx
	ret
oprintf ENDP

	END
