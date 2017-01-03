; FWRITE.ASM--
; Copyright (C) 2015 Doszip Developers

include stdio.inc
include io.inc
include errno.inc
include string.inc

	.code

fwrite PROC _CType PUBLIC USES bx di si buf:DWORD, rsize:size_t, num:size_t, fp:DWORD
local total:size_t
local bufsize:size_t
	mov	si,WORD PTR buf
	mov	ax,rsize
	mul	num
	mov	di,ax
	mov	total,ax
	test	ax,ax
	jz	fwrite_07
	les	bx,fp
	mov	dx,_MAXIOBUF
	mov	ax,es:[bx].S_FILE.iob_flag
	and	ax,_IOMYBUF or _IONBF or _IOYOURBUF
	jz	fwrite_01
	mov	dx,es:[bx].S_FILE.iob_bufsize
    fwrite_01:
	mov	bufsize,dx
    fwrite_02:
	xor	ax,ax
	cmp	di,ax
	je	fwrite_06
	mov	ax,es:[bx].S_FILE.iob_flag
	and	ax,_IOMYBUF or _IOYOURBUF
	jz	fwrite_04
	mov	ax,es:[bx].S_FILE.iob_cnt
	test	ax,ax
	jz	fwrite_04
	cmp	ax,di
	jb	fwrite_03
	mov	ax,di
    fwrite_03:
	push	ax
	mov	dx,WORD PTR es:[bx].S_FILE.iob_bp[2]
	push	es
	invoke	memcpy,es:[bx].S_FILE.iob_bp,dx::si,ax
	pop	es
	pop	ax
	sub	di,ax
	sub	es:[bx].S_FILE.iob_cnt,ax
	add	WORD PTR es:[bx].S_FILE.iob_bp,ax
	add	si,ax
	jmp	fwrite_02
    fwrite_04:
	mov	ax,di
	cmp	ax,bufsize
	jb	fwrite_05
	mov	ax,es:[bx].S_FILE.iob_flag
	and	ax,_IOMYBUF or _IOYOURBUF
	jz	fwrite_04B
	invoke	fflush,es::bx
	test	ax,ax
	jz	fwrite_04B
    fwrite_04A:
	mov	ax,total
	sub	ax,di
	xor	dx,dx
	div	rsize
	jmp	fwrite_07
    fwrite_04B:
	mov	ax,di
	mov	cx,bufsize
	test	cx,cx
	jz	fwrite_04C
	xor	dx,dx
	div	cx
	mov	ax,di
	sub	ax,dx
    fwrite_04C:
	push	ax
	les	bx,fp
	mov	dx,WORD PTR buf+2
	invoke	write,es:[bx].S_FILE.iob_file,dx::si,ax
	les	bx,fp
	pop	dx
	cmp	ax,-1
	jne	fwrite_04E
    fwrite_04D:
	or	es:[bx].S_FILE.iob_flag,_IOERR
	jmp	fwrite_04A
    fwrite_04E:
	sub	di,ax
	add	si,ax
	cmp	ax,dx
	jb	fwrite_04D
	jmp	fwrite_02
    fwrite_05:
	les	ax,buf
	mov	al,es:[si]
	mov	ah,0
	invoke	_flsbuf,ax,fp
	les	bx,fp
	cmp	ax,-1
	je	fwrite_04A
	inc	si
	dec	di
	mov	ax,es:[bx].S_FILE.iob_bufsize
	cmp	ax,0
	jg	fwrite_05A
	mov	ax,1
    fwrite_05A:
	mov	bufsize,ax
	jmp	fwrite_02
    fwrite_06:
	mov	ax,num
    fwrite_07:
	ret
fwrite	ENDP

	END
