; CMCOMPAR.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include dir.inc
include dos.inc
include fblk.inc
include string.inc
include conio.inc

_DATA	segment

cp_identical db 'The two folders seems',10
	     db 'to be identical',0
cp_different db 'Only one panel use Short File Names',0

_DATA	ENDS

_DZIP	segment

cmcompare PROC _CType PUBLIC USES si di
local fcb_A:DWORD
local fcb_B:DWORD
local fblk_A:DWORD
local fblk_B:DWORD
local count_A:WORD
local count_B:WORD
local loopc_A:WORD
local loopc_B:WORD
local equal_C:WORD
	mov	si,panela
	mov	di,panelb
	cmp	si,cpanel
	je	@F
	xchg	si,di			; Set SI to current panel
      @@:
	call	panel_stateab		; Need two panels
	jz	cmcompare_end
	mov	bx,[si]
	mov	ax,[bx]
	mov	bx,[di]
	mov	dx,[bx]
	and	ax,_W_LONGNAME		; Need equal file names
	and	dx,_W_LONGNAME
	cmp	ax,dx
	jne	cmcompare_different
	mov	bx,WORD PTR [si].S_PANEL.pn_wsub
	movmx	fcb_A,[bx].S_WSUB.ws_fcb	; fblk **A
	mov	bx,WORD PTR [di].S_PANEL.pn_wsub
	movmx	fcb_B,[bx].S_WSUB.ws_fcb	; fblk **B
	mov	ax,[si].S_PANEL.pn_fcb_count
	mov	count_A,ax		; count A
	mov	loopc_A,ax
	mov	cx,ax
	mov	ax,[di].S_PANEL.pn_fcb_count
	mov	count_B,ax		; count B
	mov	loopc_B,ax
	push	ds			; Select all files in both panels
	push	si
	les	bx,fcb_A
      @@:
	test	cx,cx
	jz	@F
	dec	cx
	lds	si,es:[bx]
	or	[si].S_FBLK.fb_flag,_A_SELECTED
	add	bx,4
	test	[si].S_FBLK.fb_flag,_A_SUBDIR
	jz	@B
	and	[si].S_FBLK.fb_flag,not _A_SELECTED
	dec	count_A
	jmp	@B
      @@:
	les	bx,fcb_B
      @@:
	test	ax,ax
	jz	@F
	dec	ax
	lds	si,es:[bx]
	or	[si].S_FBLK.fb_flag,_A_SELECTED
	add	bx,4
	test	BYTE PTR [si].S_FBLK.fb_flag,_A_SUBDIR
	jz	@B
	and	[si].S_FBLK.fb_flag,not _A_SELECTED
	dec	count_B
	jmp	@B
      @@:
	pop	si
	pop	ds	; If both panels have zero files they are identical
	mov	ax,count_A
	add	ax,count_B
	jz	cmcompare_identical
    cmcompare_08:		; If one of the panels have zero files
	xor	ax,ax		; then everything is ok (selected)
	cmp	ax,count_A
	je	@F
	cmp	ax,count_B
	jne	cmcompare_10
      @@:
	call	COMPARE_UPDATE
	jmp	cmcompare_end
    cmcompare_10:		; Compare file blocks and de-select if equal
	mov	equal_C,ax	; Number of identical files
	mov	loopc_A,ax	; Loop count A
    cmcompare_11:
	mov	ax,[si].S_PANEL.pn_fcb_count
	mov	ax,loopc_A
	cmp	ax,[si].S_PANEL.pn_fcb_count
	jnb	cmcompare_14
	xor	ax,ax
	mov	loopc_B,ax
    cmcompare_12:
	mov	ax,[di].S_PANEL.pn_fcb_count
	mov	ax,loopc_B
	cmp	ax,[di].S_PANEL.pn_fcb_count
	jnb	@F
	les	bx,fcb_B
	shl	ax,2
	add	bx,ax
	movmx	fblk_B,es:[bx]
	les	bx,es:[bx]
	test	BYTE PTR es:[bx],_A_SUBDIR
	jnz	cmcompare_15
	call	COMPARE_FB
	test	al,al
	jz	cmcompare_15
	les	bx,fblk_B
	mov	ax,es:[bx]
	and	ax,not _A_SELECTED
	mov	es:[bx],ax
	les	bx,fblk_A
	mov	ax,es:[bx]
	and	ax,not _A_SELECTED
	mov	es:[bx],ax
	inc	equal_C
      @@:
	inc	loopc_A
	jmp	cmcompare_11
    cmcompare_15:
	inc	loopc_B
	jmp	cmcompare_12
    cmcompare_14:
	call	COMPARE_UPDATE
	mov	ax,count_A
	cmp	ax,count_B
	jne	cmcompare_end
	cmp	ax,equal_C
	jne	cmcompare_end
    cmcompare_identical:
	mov	dx,offset cp_identical
	jmp	cmcompare_print
    cmcompare_different:
	mov	dx,offset cp_different
    cmcompare_print:
	invoke	stdmsg,addr cp_compare,ds::dx
    cmcompare_end:
	ret
COMPARE_UPDATE:
	invoke	panel_putitem,si,0
	invoke	panel_putitem,di,0
	retn
COMPARE_FB:
	push	ds
	push	si
	push	di
	lds	si,fcb_A
	mov	ax,loopc_A
	shl	ax,2
	add	si,ax
	lds	si,[si]
	mov	WORD PTR fblk_A,si
	mov	WORD PTR fblk_A+2,ds
	mov	di,bx
	cld
	lodsw
	mov	dl,al
	sub	ax,ax
	and	dl,_A_SUBDIR
	jnz	@F
	add	di,2
	push	di
	add	di,8
	mov	cx,-1
	repne	scasb
	pop	di
	not	cx
	add	cx,8
	repe	cmpsb
	jne	@F
	inc	ax
      @@:
	pop	di
	pop	si
	pop	ds
	retn
cmcompare ENDP

_DZIP	ENDS

	END
