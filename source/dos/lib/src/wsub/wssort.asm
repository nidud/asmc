; WSSORT.ASM--
; Copyright (C) 2015 Doszip Developers

include string.inc
include fblk.inc
include dos.inc
include wsub.inc
include stdlib.inc

.data
flag	dw ?

.code

compare PROC _CType PRIVATE USES si di bx a:DWORD, b:DWORD
	les	si,a
	les	si,es:[si]
	mov	ax,WORD PTR es:[si].S_FBLK.fb_name
	cmp	ax,'..'
	jne	@F
	mov	al,es:[si].S_FBLK.fb_name[2]
	test	al,al
	jnz	@F
	jmp	below
     @@:
	mov	ax,es:[si]
	mov	bx,es
	les	di,b
	les	di,es:[di]
	mov	dx,es:[di]
	and	dx,_A_SUBDIR
	and	ax,_A_SUBDIR
	mov	cx,flag
	jz	l1
	test	dx,dx
	jz	l1
	test	cx,_W_SORTSUB
	jnz	l2
	mov	cx,_W_SORTNAME
	jmp	l3
l1:	or	ax,dx
	jz	l2
	mov	cx,_W_SORTSUB
	jmp	l3
l2:	and	cx,_W_SORTSIZE
l3:	cmp	cx,_W_SORTTYPE
	je	ftype
	cmp	cx,_W_SORTDATE
	je	fdate
	cmp	cx,_W_SORTSIZE
	je	fsize
	cmp	cx,_W_SORTSUB
	je	subdir
	jmp	fname
ftype:	add	di,S_FBLK.fb_name
	add	si,S_FBLK.fb_name
	push	es
	invoke	strext,es::di
	push	ax
	invoke	strext,bx::si
	pop	dx
	pop	es
	jz	@F
	test	dx,dx
	jz	above
	push	es
	invoke	stricmp,bx::ax,es::dx
	pop	es
	jz	ftequ
	jmp	toend
     @@:
	test	dx,dx
	jnz	below
ftequ:	invoke	stricmp,bx::si,es::di
	jmp	toend
fdate:	mov	ax,es
	mov	es,bx
	mov	dx,WORD PTR es:[si].S_FBLK.fb_time[2]
	mov	cx,WORD PTR es:[si].S_FBLK.fb_time
	mov	es,ax
	cmp	dx,WORD PTR es:[di].S_FBLK.fb_time[2]
	jb	above
	ja	below
	cmp	cx,WORD PTR es:[di].S_FBLK.fb_time
	jb	above
	ja	below
	jmp	fname
fsize:	mov	ax,es
	mov	es,bx
	mov	cx,WORD PTR es:[si].S_FBLK.fb_size[2]
	mov	es,ax
	cmp	cx,WORD PTR es:[di].S_FBLK.fb_size[2]
	jb	above
	ja	below
	mov	es,bx
	mov	cx,WORD PTR es:[si].S_FBLK.fb_size
	mov	es,ax
	cmp	cx,WORD PTR es:[di].S_FBLK.fb_size
	jb	above
	ja	below
	jmp	fname
subdir: test	es:[di].S_FBLK.fb_flag,_A_SUBDIR
	jnz	above
below:	mov	ax,-1
	jmp	toend
above:	mov	ax,1
	jmp	toend
fname:	add	di,S_FBLK.fb_name
	add	si,S_FBLK.fb_name
	invoke	stricmp,bx::si,es::di
toend:	ret
compare ENDP

wssort	PROC _CType PUBLIC wsub:DWORD
	push	bx
	les	bx,wsub
	mov	cx,es:[bx].S_WSUB.ws_count
	mov	ax,WORD PTR es:[bx].S_WSUB.ws_fcb
	mov	dx,WORD PTR es:[bx].S_WSUB.ws_fcb[2]
	les	bx,es:[bx].S_WSUB.ws_flag
	mov	bx,es:[bx]
	mov	flag,bx
	mov	bx,compare
	invoke	qsort,dx::ax,cx,4,cs::bx
	pop	bx
	ret
wssort	ENDP

	END
