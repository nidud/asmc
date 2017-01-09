; CMCOMPARE.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include io.inc
include string.inc

	.data

externdef	cp_compare:byte
cp_identical	db "The two folders seems",10,"to be identical",0
cp_different	db "Only one panel use Long File Names",0

	.code

cmcompare proc uses esi edi ebx

  local fcb_A, fcb_B, fblk_A, fblk_B,
	count_A, count_B, loopc_A, loopc_B, equal_C

	mov	esi,panela
	mov	edi,panelb
	cmp	esi,cpanel
	je	@F
	xchg	esi,edi			; Set SI to current panel
@@:
	call	panel_stateab		; Need two panels
	jz	toend
	mov	ebx,[esi]
	mov	eax,[ebx]
	mov	ebx,[edi]
	mov	edx,[ebx]
	and	eax,_W_LONGNAME		; Need equal file names
	and	edx,_W_LONGNAME
	cmp	eax,edx
	jne	different
	mov	eax,[esi].S_PANEL.pn_wsub
	mov	eax,[eax].S_WSUB.ws_fcb
	mov	fcb_A,eax		; fblk **A
	mov	eax,[edi].S_PANEL.pn_wsub
	mov	eax,[eax].S_WSUB.ws_fcb
	mov	fcb_B,eax		; fblk **B
	mov	eax,[esi].S_PANEL.pn_fcb_count
	mov	count_A,eax		; count A
	mov	loopc_A,eax
	mov	ecx,eax
	mov	eax,[edi].S_PANEL.pn_fcb_count
	mov	count_B,eax		; count B
	mov	loopc_B,eax
	push	esi			; Select all files in both panels
	mov	ebx,fcb_A
@@:
	test	ecx,ecx
	jz	@F
	dec	ecx
	mov	esi,[ebx]
	or	[esi].S_FBLK.fb_flag,_FB_SELECTED
	add	ebx,4
	test	[esi].S_FBLK.fb_flag,_A_SUBDIR
	jz	@B
	and	[esi].S_FBLK.fb_flag,not _FB_SELECTED
	dec	count_A
	jmp	@B
@@:
	mov	ebx,fcb_B
@@:
	test	eax,eax
	jz	@F
	dec	eax
	mov	esi,[ebx]
	or	[esi].S_FBLK.fb_flag,_FB_SELECTED
	add	ebx,4
	test	byte ptr [esi].S_FBLK.fb_flag,_A_SUBDIR
	jz	@B
	and	[esi].S_FBLK.fb_flag,not _FB_SELECTED
	dec	count_B
	jmp	@B
@@:
	pop	esi		; If both panels have zero files they are identical
	mov	eax,count_A
	add	eax,count_B
	jz	identical
cmcompare_08:			; If one of the panels have zero files
	xor	eax,eax		; then everything is ok (selected)
	cmp	eax,count_A
	je	@F
	cmp	eax,count_B
	jne	cmcompare_10
@@:
	call	COMPARE_UPDATE
	jmp	toend
cmcompare_10:			; Compare file blocks and de-select if equal
	mov	equal_C,eax	; Number of identical files
	mov	loopc_A,eax	; Loop count A
cmcompare_11:
	mov	eax,[esi].S_PANEL.pn_fcb_count
	mov	eax,loopc_A
	cmp	eax,[esi].S_PANEL.pn_fcb_count
	jnb	cmcompare_14
	xor	eax,eax
	mov	loopc_B,eax
cmcompare_12:
	mov	eax,[edi].S_PANEL.pn_fcb_count
	mov	eax,loopc_B
	cmp	eax,[edi].S_PANEL.pn_fcb_count
	jnb	cmcompare_13
	mov	ebx,fcb_B
	shl	eax,2
	add	ebx,eax
	mov	eax,[ebx]
	mov	fblk_B,eax
	mov	ebx,[ebx]
	test	byte ptr [ebx],_A_SUBDIR
	jnz	cmcompare_15
	push	esi
	push	edi
	mov	esi,fcb_A
	mov	eax,loopc_A
	shl	eax,2
	add	esi,eax
	mov	esi,[esi]
	mov	fblk_A,esi
	xor	eax,eax
	test	byte ptr [esi],_A_SUBDIR
	jnz	@F
	lea	edi,[ebx+4]
	add	esi,4
	mov	ecx,S_FBLK.fb_name - 4
	repe	cmpsb
	jne	@F
	_stricmp( edi, esi )
	test	eax,eax
	mov	eax,1
	je	@F
	dec	eax
@@:
	pop	edi
	pop	esi
	test	al,al
	jz	cmcompare_15
	mov	ebx,fblk_B
	mov	eax,[ebx]
	and	eax,not _FB_SELECTED
	mov	[ebx],eax
	mov	ebx,fblk_A
	mov	eax,[ebx]
	and	eax,not _FB_SELECTED
	mov	[ebx],eax
	inc	equal_C
cmcompare_13:
	inc	loopc_A
	jmp	cmcompare_11
cmcompare_15:
	inc	loopc_B
	jmp	cmcompare_12
cmcompare_14:
	call	COMPARE_UPDATE
	mov	eax,count_A
	cmp	eax,count_B
	jne	toend
	cmp	eax,equal_C
	jne	toend
identical:
	lea	edx,cp_identical
	jmp	print
different:
	lea	edx,cp_different
print:
	stdmsg( addr cp_compare, edx )
toend:
	ret
COMPARE_UPDATE:
	panel_putitem( esi, 0 )
	panel_putitem( edi, 0 )
	retn
cmcompare endp

	END
