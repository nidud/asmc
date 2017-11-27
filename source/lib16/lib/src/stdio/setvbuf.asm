; SETVBUF.ASM--
; Copyright (C) 2015 Doszip Developers

include stdio.inc
include alloc.inc

	.code

setvbuf PROC _CType USES si bx fp:DWORD, buf:DWORD, tp:size_t, bsize:size_t
	mov	ax,tp
	cmp	ax,_IONBF
	je	setvbuf_01
	cmp	ax,_IOLBF
	je	setvbuf_01
	cmp	ax,_IOFBF
	jne	setvbuf_00
	mov	ax,bsize
	cmp	ax,2
	jb	setvbuf_00
	cmp	ax,INT_MAX
	jbe	setvbuf_01
    setvbuf_00:
	mov	ax,-1
	jmp	setvbuf_END
    setvbuf_01:
	invoke	fflush,fp
	invoke	_freebuf,fp
	les	bx,fp
	mov	ax,[bx].S_FILE.iob_flag
	and	ax,not (_IOMYBUF or _IOYOURBUF or _IONBF or _IOSETVBUF or _IOFEOF or _IOFLRTN or _IOCTRLZ)
	mov	si,ax
	mov	ax,tp
	test	ax,_IONBF
	jz	setvbuf_02
	or	si,_IONBF
	lea	ax,[bx].S_FILE.iob_charbuf
	stom	buf
	mov	bsize,4
	jmp	setvbuf_04
    setvbuf_02:
	mov	ax,WORD PTR buf
	test	ax,ax
	jnz	setvbuf_03
	invoke	malloc,bsize
	stom	buf
	mov	ax,-1
	jz	setvbuf_END
	or	si,_IOMYBUF or _IOSETVBUF
	jmp	setvbuf_04
    setvbuf_03:
	or	si,_IOYOURBUF or _IOSETVBUF
    setvbuf_04:
	mov	[bx].S_FILE.iob_flag,si
	mov	ax,bsize
	mov	[bx].S_FILE.iob_bufsize,ax
	lodm	buf
	stom	[bx].S_FILE.iob_bp
	stom	[bx].S_FILE.iob_base
	xor	ax,ax
	mov	[bx].S_FILE.iob_cnt,ax
    setvbuf_END:
	ret
setvbuf ENDP

	END
