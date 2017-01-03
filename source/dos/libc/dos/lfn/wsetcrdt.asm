; WSETCRDT.ASM--
; Copyright (C) 2015 Doszip Developers

include dos.inc

	.code

wsetcrdate PROC _CType PUBLIC USES si di bx path:DWORD, crdate:WORD, crtime:WORD
	push	ds
	lds	dx,path
	mov	cx,crtime
	mov	di,crdate
	xor	si,si
	stc
	mov	ax,7143h
	mov	bl,7
	int	21h
	pop	ds
	jc	wsetcrdate_error
	xor	ax,ax
    wsetcrdate_toend:
	ret
    wsetcrdate_error:
	call	osmaperr
	jmp	wsetcrdate_toend
wsetcrdate ENDP

	END
