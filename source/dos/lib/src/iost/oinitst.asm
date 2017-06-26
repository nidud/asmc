; OINITST.ASM--
; Copyright (C) 2015 Doszip Developers

include iost.inc
include alloc.inc
include stdio.inc
include errno.inc
include string.inc

	.code

oinitst PROC _CType PUBLIC USES bx io:DWORD, bsize:size_t
	mov	bx,WORD PTR io
	mov	dx,[bx].S_IOST.ios_file
	invoke	memzero,io,SIZE S_IOST
	mov	[bx].S_IOST.ios_file,dx
	dec	ax
	mov	dx,ax
	stom	[bx].S_IOST.ios_bb	; CRC to FFFFFFFFh
	mov	ax,bsize
	test	ax,ax
	jz	oinitbufin
	mov	[bx].S_IOST.ios_size,ax
	invoke	malloc,ax
	jz	@F
	cmp	[bx].S_IOST.ios_size,-1
	jne	@F
	xor	ax,ax
	inc	dx
      @@:
	stom	[bx].S_IOST.ios_bp
	test	dx,dx
	ret
    oinitbufin:
	mov	[bx].S_IOST.ios_c,ax
	mov	[bx].S_IOST.ios_i,ax
	mov	[bx].S_IOST.ios_size,1000h
	mov	[bx].S_IOST.ios_flag,IO_STRINGB
	mov	ax,offset _bufin
	mov	dx,ds
	jmp	@B
oinitst ENDP

ofreest PROC _CType PUBLIC USES bx io:DWORD
	mov	bx,WORD PTR io
	sub	ax,ax
	mov	dx,WORD PTR [bx].S_IOST.ios_bp+2
	cmp	WORD PTR [bx].S_IOST.ios_bp,ax
	mov	WORD PTR [bx].S_IOST.ios_bp,ax
	mov	WORD PTR [bx].S_IOST.ios_bp+2,ax
	jne	@F
	dec	dx
      @@:
	invoke	free,dx::ax
	mov	ax,ER_MEM
	ret
ofreest ENDP

	END
