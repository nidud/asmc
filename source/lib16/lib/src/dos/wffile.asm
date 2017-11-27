; WFFILE.ASM--
; Copyright (C) 2015 Doszip Developers

include dos.inc
include string.inc

	.code

wfindnext PROC _CType PUBLIC ff:DWORD, handle:WORD
	push	si
	push	di
	push	bx
	stc
	mov	ax,714Fh
	mov	bx,handle
	mov	si,1
	les	di,ff
	int	21h
	jc	error
success:
	xor	ax,ax
toend:
	pop	bx
	pop	di
	pop	si
	ret
error:
	cmp	ax,57h
	jne	@F
	mov	ax,714Fh
	int	21h
	jnc	success
@@:
	call	osmaperr
	jmp	toend
wfindnext ENDP

wfindfirst PROC _CType PUBLIC fmask:DWORD, fblk:DWORD, attrib:WORD
	push	si
	push	di
	stc
	push	ds
	mov	ax,714Eh
	mov	si,1
	mov	cx,attrib
	les	di,fblk
	lds	dx,fmask
	int	21h
	pop	ds
	jc	error
toend:
	pop	di
	pop	si
	ret
error:
	call	osmaperr
	jmp	toend
wfindfirst ENDP

wcloseff PROC _CType PUBLIC handle:WORD
	mov	ax,71A1h
	mov	bx,handle
	int	21h
	sub	ax,ax
	ret
wcloseff ENDP

	END
