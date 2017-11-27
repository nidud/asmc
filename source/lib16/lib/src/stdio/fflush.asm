; FFLUSH.ASM--
; Copyright (C) 2015 Doszip Developers

include stdio.inc
include io.inc

	.code

fflush	PROC _CType PUBLIC USES bx di si fp:DWORD
	les	bx,fp
	sub	si,si
	mov	ax,es:[bx].S_FILE.iob_flag
	mov	di,ax
	and	ax,_IOREAD or _IOWRT
	cmp	ax,_IOWRT
	jne	fflush_02
	test	di,_IOMYBUF or _IOYOURBUF
	jz	fflush_02
	mov	ax,WORD PTR es:[bx].S_FILE.iob_bp
	sub	ax,WORD PTR es:[bx].S_FILE.iob_base
	cmp	ax,0
	jle	fflush_01
    fflush_00:
	push	ax
	invoke	write,es:[bx].S_FILE.iob_file,es:[bx].S_FILE.iob_base,ax
	les	bx,fp
	pop	dx
	cmp	ax,dx
	jne	fflush_02
	mov	ax,es:[bx].S_FILE.iob_flag
	test	ax,_IORW
	jz	fflush_02
	and	ax,not _IOWRT
	jmp	fflush_02
    fflush_01:
	or	di,_IOERR
	mov	es:[bx].S_FILE.iob_flag,di
	mov	si,-1
    fflush_02:
	movmx	es:[bx].S_FILE.iob_bp,es:[bx].S_FILE.iob_base
	sub	ax,ax
	mov	es:[bx].S_FILE.iob_cnt,ax
    fflush_04:
	mov	ax,si
	ret
fflush	ENDP

	END
