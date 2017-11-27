; WSETWRDT.ASM--
; Copyright (C) 2015 Doszip Developers

include dos.inc

	.code

wsetwrdate PROC _CType PUBLIC USES di bx path:DWORD, wrdate:WORD, wrtime:WORD
	push	ds
	lds	dx,path
	mov	cx,wrtime
	mov	di,wrdate
	stc
	mov	ax,7143h
	mov	bl,3
	int	21h
	pop	ds
	jc	wsetwrdate_error
	xor	ax,ax
    wsetwrdate_end:
	ret
    wsetwrdate_error:
	call	osmaperr
	jmp	wsetwrdate_end
wsetwrdate ENDP

	END
