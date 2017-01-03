; FSEEK.ASM--
; Copyright (C) 2015 Doszip Developers

include stdio.inc
include io.inc
include errno.inc

	.code

fseek	PROC _CType PUBLIC USES di fp:DWORD, off:DWORD, whence:size_t
	push	si
	les	di,fp
	mov	si,es
	mov	ax,whence
	cmp	ax,SEEK_SET
	jl	fseek_00
	cmp	ax,SEEK_END
	ja	fseek_00
	mov	dx,ax
	mov	ax,es:[di].S_FILE.iob_flag
	test	ax,_IOREAD or _IOWRT or _IORW
	jnz	fseek_01
    fseek_00:
	mov	errno,EINVAL
	mov	ax,-1
	jmp	fseek_END
    fseek_01:
	and	ax,not _IOEOF
	mov	es:[di].S_FILE.iob_flag,ax
	cmp	dx,SEEK_CUR
	jne	fseek_02
	invoke	ftell,fp
	add	WORD PTR off,ax
	adc	WORD PTR off+2,dx
	mov	whence,SEEK_SET
    fseek_02:
	invoke	fflush,fp
	mov	es,si
	mov	ax,es:[di].S_FILE.iob_flag
	test	ax,_IORW
	jz	fseek_03
	and	ax,not (_IOWRT or _IOREAD)
	mov	es:[di].S_FILE.iob_flag,ax
	jmp	fseek_04
    fseek_03:
	test	ax,_IOREAD
	jz	fseek_04
	test	ax,_IOMYBUF
	jz	fseek_04
	test	ax,_IOSETVBUF
	jnz	fseek_04
	mov	es:[di].S_FILE.iob_bufsize,_MINIOBUF
    fseek_04:
	invoke	lseek, es:[di].S_FILE.iob_file, off, whence
	cmp	ax,-1
	je	fseek_END
    fseek_05:
	xor	ax,ax
    fseek_END:
	pop	si
	ret
fseek	ENDP

	END
