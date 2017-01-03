; FCLOSE.ASM--
; Copyright (C) 2015 Doszip Developers

include stdio.inc
include io.inc

	.code

fclose PROC _CType PUBLIC USES si bx fp:DWORD
	sub	si,si
	les	bx,fp
	dec	si
	mov	ax,es:[bx].S_FILE.iob_flag
	and	ax,_IOREAD or _IOWRT or _IORW
	jz	fclose_01
	invoke	fflush,fp
	mov	si,ax
	invoke	_freebuf,fp
	invoke	close,es:[bx].S_FILE.iob_file
	cmp	ax,0
	jge	fclose_00
	mov	si,-1
    fclose_00:
	les	bx,fp
	xor	ax,ax
	mov	es:[bx].S_FILE.iob_flag,ax
	dec	ax
	mov	es:[bx].S_FILE.iob_file,ax
    fclose_01:
	mov	ax,si
	ret
fclose	ENDP

	END
