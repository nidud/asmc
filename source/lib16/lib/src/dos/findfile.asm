; FINDFILE.ASM--
; Copyright (C) 2015 Doszip Developers

include dos.inc

	.code

findfirst PROC _CType PUBLIC USES bx file:DWORD, fblk:DWORD, attr:WORD
	push	ds
	mov	ah,2Fh
	int	21h
	push	es
	push	bx
	mov	ah,1Ah
	lds	dx,fblk
	int	21h
	mov	ah,4Eh
	mov	cx,attr
	lds	dx,file
	int	21h
	pushf
	pop	cx
	xchg	ax,bx
	mov	ah,1Ah
	pop	dx
	pop	ds
	int	21h
	push	cx
	popf
	pop	ds
	jc	error
	xor	ax,ax
toend:
	ret
error:
	call	osmaperr
	jmp	toend
findfirst ENDP

findnext PROC _CType PUBLIC USES bx fblk:DWORD
	push	ds
	mov	ah,2Fh
	int	21h
	push	es
	push	bx
	mov	ah,1Ah
	lds	dx,fblk
	int	21h
	mov	ah,4Fh
	int	21h
	pushf
	pop	cx
	xchg	ax,bx
	mov	ah,1Ah
	pop	dx
	pop	ds
	int	21h
	push	cx
	popf
	pop	ds
	jc	error
	xor	ax,ax
toend:
	ret
error:
	call	osmaperr
	jmp	toend
findnext ENDP

	END
