include alloc.inc
include string.inc
include iost.inc
include wsub.inc
include zip.inc

ZIP_CENTRALID	equ 02014B50h	; signature central file
ZIP_ENDSENTRID	equ 06054B50h	; signature end central

	.data

arc_pathz	dd 0

	.code

	OPTION	PROC: PRIVATE

getendcentral PROC wsub, zend
	wsopenarch( wsub )
	mov	STDI.ios_file,eax
	inc	eax
	jz	toend
	ioseek( addr STDI, 0, SEEK_END )
	jz	error
	mov	zip_flength,eax
	cmp	eax,SIZE S_ZEND
	jb	error
	call	oungetc
	jz	error
	cmp	STDI.ios_i,SIZE S_ZEND-1
	jb	toend
	sub	STDI.ios_i,SIZE S_ZEND-2
@@:
	call	oungetc
	jz	toend
	cmp	al,'P'
	jne	@B
	mov	eax,SIZE S_ZEND
	call	oread
	jz	toend
	cmp	DWORD PTR [eax],ZIP_ENDSENTRID
	jne	@B
	memcpy( zend, eax, SIZE S_ZEND )
	mov	eax,1
toend:
	test	eax,eax
	ret
error:
	_close( STDI.ios_file )
	xor	eax,eax
	jmp	toend
getendcentral ENDP

zip_allocfblk PROC USES esi edi ebx
	mov	edi,eax
	mov	esi,entryname
	strlen( esi )
	add	eax,SIZE S_FBLK
	push	eax
	add	eax,12
	malloc( eax )
	pop	ecx
	jz	toend
	mov	ebx,eax
	mov	ax,zip_central.cz_ext_attrib
	and	eax,_A_FATTRIB
	or	eax,zip_attrib
	mov	[ebx],eax
	cmp	edi,2
	jne	alloc_file
	mov	edi,ecx
	cmp	zip_central.cz_version_made,0
	jne	@F
	test	BYTE PTR zip_central.cz_ext_attrib,_A_SUBDIR
	jnz	set_block
@@:
	mov	eax,_A_SUBDIR
	or	eax,zip_attrib
	mov	[ebx],eax
	jmp	set_block
alloc_file:
	mov	edi,ecx
	sub	eax,eax
	mov	DWORD PTR [ebx].S_FBLK.fb_size[4],eax
	mov	eax,zip_central.cz_fsize
	mov	DWORD PTR [ebx].S_FBLK.fb_size,eax
set_block:
	push	ebx
	mov	ax,zip_central.cz_date
	shl	eax,16
	mov	ax,zip_central.cz_time
	mov	[ebx].S_FBLK.fb_time,eax
	add	ebx,S_FBLK.fb_name
	strcpy( ebx, esi )
	sub	eax,S_FBLK.fb_name
	add	edi,eax
	mov	eax,zip_central.cz_off_local
	mov	[edi],eax
	mov	eax,zip_central.cz_csize
	mov	[edi+4],eax
	mov	eax,zip_central.cz_crc
	mov	[edi+8],eax
	pop	eax
toend:
	ret
zip_allocfblk ENDP

zip_readcentral PROC USES esi edi
	mov	eax,SIZE S_CZIP
	call	oread
	mov	ebx,eax
	jz	toend
	xor	eax,eax
	cmp	DWORD PTR [ebx],ZIP_CENTRALID
	jne	toend
	add	STDI.ios_i,SIZE S_CZIP
	dec	eax
	mov	edx,arc_pathz
	cmp	[ebx].S_CZIP.cz_fnsize,dx
	jbe	toend
	mov	edi,offset zip_central
	mov	eax,ecx
	mov	esi,ebx
	mov	ecx,SIZE S_CZIP / 4
	rep	movsd
	movsw
	movzx	ecx,[ebx].S_CZIP.cz_fnsize
	add	ebx,SIZE S_CZIP
	sub	eax,SIZE S_CZIP
	cmp	eax,ecx
	jae	@F
	mov	eax,ecx
	call	oread
	mov	ebx,eax
	jz	toend
	movzx	ecx,zip_central.cz_fnsize
@@:
	mov	esi,ebx
	mov	edi,entryname
	mov	ah,'\'
@@:
	test	ecx,ecx
	jz	@F
	sub	ecx,1
	mov	al,[esi]
	mov	[edi],al
	add	edi,1
	add	esi,1
	cmp	al,'/'
	jne	@B
	mov	[edi-1],ah
	jmp	@B
@@:
	mov	BYTE PTR [edi],0
	movzx	eax,zip_central.cz_fnsize
	add	STDI.ios_i,eax
	mov	ecx,eax
	mov	eax,_FB_ARCHZIP or _A_ARCH
	test	BYTE PTR zip_central.cz_bitflag,1
	jz	@F
	or	eax,_FB_ZENCRYPTED
@@:
	test	BYTE PTR zip_central.cz_bitflag,8
	jz	@F
	or	eax,_FB_ZEXTLOCHD
@@:
	mov	zip_attrib,eax
	cmp	BYTE PTR [edi-1],'\'
	jne	@F
	mov	BYTE PTR [edi-1],0
	or	zip_attrib,_A_SUBDIR
	dec	zip_central.cz_fnsize
@@:
	movzx	edi,zip_central.cz_extsize
	add	di,zip_central.cz_cmtsize
	jz	@F
	mov	eax,edi
	call	oread
	mov	ebx,eax
	jz	toend
	add	STDI.ios_i,edi
@@:
	mov	eax,1
toend:
	test	eax,eax
	ret
zip_readcentral ENDP

zip_testcentral PROC USES esi wsub
	mov	eax,wsub
	mov	esi,entryname
	mov	eax,[eax].S_WSUB.ws_arch
	cmp	BYTE PTR [eax],0
	je	@F
	strncmp( eax, esi, arc_pathz )
	mov	eax,0
	jnz	toend
@@:
	mov	eax,arc_pathz
	test	eax,eax
	jz	@F
	cmp	BYTE PTR [esi+eax],'\'
	jne	null
	inc	eax
	add	eax,esi
	strcpy( esi, eax )
@@:
	cmp	BYTE PTR [esi],','
	jne	@F
	strcpy( esi, addr [esi+1] )
	jmp	@B
@@:
	strchr( esi, '\' )
	jz	@F
	mov	BYTE PTR [eax],0
	wsearch( wsub, esi )
	inc	eax
	mov	eax,2
	jz	toend
	xor	eax,eax
	jmp	toend
@@:
	wsearch( wsub, esi )
	inc	eax
	mov	eax,1
	jz	toend
	dec	eax
	mov	edx,wsub
	mov	edx,[edx].S_WSUB.ws_fcb
	mov	edx,[edx+eax*4]
	mov	ax,zip_central.cz_date
	shl	eax,16
	mov	ax,zip_central.cz_time
	mov	[edx].S_FBLK.fb_time,eax
	cmp	zip_central.cz_version_made,0
	jne	null
	mov	eax,zip_attrib
	or	ax,zip_central.cz_ext_attrib
	and	eax,_A_FATTRIB
	mov	[edx],eax
null:
	xor	eax,eax
toend:
	ret
zip_testcentral ENDP

zip_findnext PROC
	call	zip_readcentral
	jz	toend
	inc	eax
	jz	read
	zip_testcentral( edi )
	jmp	alloc
read:
	movzx	eax,[ebx].S_CZIP.cz_extsize
	add	ax,[ebx].S_CZIP.cz_cmtsize
	add	ax,[ebx].S_CZIP.cz_fnsize
	push	eax
	call	oread
	mov	ebx,eax
	pop	edx
	jz	toend
	add	STDI.ios_i,edx
	xor	eax,eax
alloc:
	test	eax,eax
	jz	zip_findnext
	call	zip_allocfblk
toend:
	ret
zip_findnext ENDP

	OPTION	PROC: PUBLIC

wzipread PROC USES esi edi ebx wsub

  local fblk:DWORD

	xor	eax,eax
	mov	STDI.ios_i,eax
	mov	STDI.ios_c,eax
	mov	STDI.ios_flag,eax
	alloca( 10000h )
	mov	STDI.ios_size,10000h
	mov	STDI.ios_bp,eax
	mov	eax,wsub
	strlen( [eax].S_WSUB.ws_arch )
	mov	arc_pathz,eax
	mov	edi,wsub
	wsfree( edi )
	getendcentral( edi, addr zip_endcent )
	jz	error
	fbupdir( _FB_ARCHZIP )
	mov	[edi].S_WSUB.ws_count,1
	mov	edx,[edi].S_WSUB.ws_fcb
	mov	[edx],eax
	oseek ( zip_endcent.ze_off_cent, SEEK_SET )
lup:
	call	zip_findnext
	mov	fblk,eax
	test	eax,eax
	jz	break
	mov	cl,[eax]
	test	cl,_A_SUBDIR
	jnz	@F
	add	eax,S_FBLK.fb_name
	cmpwarg( eax, [edi].S_WSUB.ws_mask )
	jnz	@F
	free( fblk )
	jmp	lup
@@:
	mov	ecx,fblk
	mov	eax,[edi].S_WSUB.ws_count
	mov	edx,[edi].S_WSUB.ws_fcb
	mov	[edx+eax*4],ecx
	inc	eax
	mov	[edi].S_WSUB.ws_count,eax
	cmp	eax,[edi].S_WSUB.ws_maxfb
	jb	lup
break:
	ioclose( addr STDI )
	mov	eax,[edi].S_WSUB.ws_count
toend:
	ret
error:
	mov	eax,-2
	jmp	toend
wzipread ENDP

	END
