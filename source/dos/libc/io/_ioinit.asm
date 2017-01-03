; _IOINIT.ASM--
; Copyright (C) 2015 Doszip Developers

include io.inc

extrn	_psp:WORD
PUBLIC	_nfile
PUBLIC	_osfile

.data

_nfile	dw _NFILE_
_osfile db FH_OPEN or FH_DEVICE or FH_TEXT
	db FH_OPEN or FH_DEVICE or FH_TEXT
	db FH_OPEN or FH_DEVICE or FH_TEXT
	db _NFILE_ - 3 dup(0)

	.code

_ioinit PROC PRIVATE
	push	di
	push	si
	cmp	_nfile,5
	jbe	ioinit_03
	mov	es,_psp
	mov	di,29
	mov	si,offset _osfile
	mov	cx,5
	add	si,cx
    ioinit_00:
	mov	al,es:[di]
	cmp	al,0FFh
	je	ioinit_01
	or	BYTE PTR [si],(FH_TEXT or FH_OPEN)
	mov	ax,4400h
	mov	bx,cx
	int	21h
	and	dx,128
	jz	ioinit_02
	or	BYTE PTR [si],FH_DEVICE
	jmp	ioinit_02
    ioinit_01:
	mov	BYTE PTR [si],0
    ioinit_02:
	inc	si
	inc	di
	inc	cx
	cmp	cx,_nfile
	jb	ioinit_00
    ioinit_03:
	pop	si
	pop	di
	ret
_ioinit ENDP

pragma_init _ioinit, 1

	END
