; FREAD.ASM--
; Copyright (C) 2015 Doszip Developers

include stdio.inc
include io.inc
include errno.inc
include string.inc

	.code

fread PROC _CType PUBLIC USES bx di si buf:DWORD, rsize:size_t, num:size_t, fp:DWORD
local p:DWORD
local total:size_t
local nbytes:size_t
local nread:size_t
	movmx	p,buf
	mov	ax,rsize
	mul	num
	mov	total,ax
	mov	si,ax
	test	ax,ax
	jz	fread_END
	les	bx,fp
	mov	dx,es:[bx].S_FILE.iob_bufsize
	mov	ax,es:[bx].S_FILE.iob_flag
	and	ax,_IOMYBUF or _IONBF or _IOYOURBUF
	jnz	fread_00
	mov	dx,_MAXIOBUF
    fread_00:
	mov	di,dx
    fread_01:
	test	si,si
	jz	fread_BREAK
	mov	ax,es:[bx].S_FILE.iob_flag
	and	ax,_IOMYBUF or _IONBF or _IOYOURBUF
	jz	fread_02
	mov	ax,es:[bx].S_FILE.iob_cnt
	test	ax,ax
	jz	fread_02
	cmp	si,ax
	jg	fread_01B
	mov	ax,si
    fread_01B:
	mov	nbytes,ax
	invoke	memcpy,p,es:[bx].S_FILE.iob_bp,ax
	les	bx,fp
	mov	ax,nbytes
	sub	si,ax
	sub	es:[bx].S_FILE.iob_cnt,ax
	add	WORD PTR es:[bx].S_FILE.iob_bp,ax
	add	WORD PTR p,ax
	jmp	fread_01
    fread_02:
	mov	ax,si
	mov	cx,di
	cmp	ax,cx
	jb	fread_03
	test	cx,cx
	jz	fread_02A
	xor	dx,dx
	div	cx
	mov	ax,si
	sub	ax,dx
    fread_02A:
	mov	nbytes,ax
	invoke	read,es:[bx].S_FILE.iob_file,p,ax
	les	bx,fp
	mov	nread,ax
	test	ax,ax
	jnz	fread_02B
	or	es:[bx].S_FILE.iob_flag,_IOEOF
	jmp	fread_02C
    fread_02B:
	cmp	ax,-1
	jne	fread_02D
	or	es:[bx].S_FILE.iob_flag,_IOERR
    fread_02C:
	mov	ax,total
	sub	ax,si
	xor	dx,dx
	div	rsize
	jmp	fread_END
    fread_02D:
	sub	si,ax
	add	WORD PTR p,ax
	jmp	fread_01
    fread_03:
	invoke	_filebuf,fp
	cmp	ax,-1
	je	fread_02C
	les	bx,p
	mov	es:[bx],al
	inc	WORD PTR p
	les	bx,fp
	dec	si
	mov	ax,es:[bx].S_FILE.iob_bufsize
	mov	di,ax
	jmp	fread_01
    fread_BREAK:
	mov	ax,num
    fread_END:
	ret
fread	ENDP

	END
