; READ.ASM--
; Copyright (C) 2015 Doszip Developers

include io.inc
include errno.inc

ER_ACCESS_DENIED equ 5
ER_BROKEN_PIPE	 equ 109

	.data

pipech	db _NFILE_ dup(10)
peekchr db 0

	.code

read	PROC _CType PUBLIC USES bx si di h:size_t, b:DWORD, l:size_t
	sub	si,si
	les	di,b
	mov	bx,h
	mov	al,_osfile[bx]
	test	al,FH_EOF
	jnz	read_nul
	cmp	l,si
	je	read_nul
	test	al,FH_PIPE or FH_DEVICE
	jz	read_start
	mov	al,pipech[bx]
	cmp	al,10
	je	read_start
	mov	es:[di],al
	mov	[pipech+bx],10
	inc	di
	inc	si
	dec	l
    read_start:
	invoke	osread,bx,es::di,l
	test	ax,ax
	jnz	read_03
	cmp	doserrno,ER_BROKEN_PIPE
	je	read_nul
	dec	ax
	cmp	doserrno,ER_ACCESS_DENIED
	jne	read_toend
	mov	errno,EBADF
    read_toend:
	jmp	read_end
    read_nul:
	sub	ax,ax
	jmp	read_end
    read_03:
	add	si,ax
	les	di,b
	mov	bx,h
	mov	al,_osfile[bx]
	test	al,FH_TEXT
	jz	read_16
	and	al,not FH_CRLF
	cmp	BYTE PTR es:[di],10
	jne	read_04
	or	al,FH_CRLF
    read_04:
	mov	_osfile[bx],al
	mov	dx,di
    read_05:
	mov	ax,WORD PTR b
	add	ax,si
	cmp	di,ax
	jnb	read_06
	cmp	BYTE PTR es:[di],26
	jne	read_07
	mov	bx,h
	test	_osfile[bx],FH_DEVICE
	jnz	read_06
	or	_osfile[bx],FH_EOF
    read_06:
	jmp	read_15
    read_07:
	cmp	BYTE PTR es:[di],13
	je	read_09
    read_08:
	mov	al,es:[di]
	mov	bx,dx
	mov	es:[bx],al
	inc	di
	inc	dx
	jmp	read_05
    read_09:
	mov	ax,WORD PTR b
	add	ax,si
	dec	ax
	cmp	di,ax
	jnb	read_10
	cmp	BYTE PTR es:[di][1],10
	jne	read_08
	add	di,2
	mov	al,10
	jmp	read_11
    read_10:
	inc	di
	push	es
	push	dx
	invoke	osread,h,addr peekchr,1
	pop	dx
	pop	es
	test	ax,ax
	jnz	read_12
	mov	al,13
    read_11:
	mov	bx,dx
	mov	es:[bx],al
	inc	dx
	jmp	read_05
    read_12:
	mov	bx,h
	test	_osfile[bx],FH_DEVICE or FH_PIPE
	jz	read_13
	mov	al,10
	cmp	peekchr,al
	je	read_11
	mov	al,peekchr
	mov	pipech[bx],al
	mov	al,13
	jmp	read_11
    read_13:
	cmp	dx,WORD PTR b
	jne	read_14
	mov	al,10
	cmp	peekchr,al
	je	read_11
    read_14:
	push	es
	push	dx
	invoke	lseek,bx,-1,SEEK_CUR
	pop	dx
	pop	es
	mov	al,13
	cmp	peekchr,10
	jne	read_11
	jmp	read_05
    read_15:
	mov	si,dx
	sub	si,WORD PTR b
    read_16:
	mov	ax,si
    read_end:
	ret
read	ENDP

	END
