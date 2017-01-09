include string.inc
include wsub.inc
include iost.inc
include zip.inc

	.code

zip_copylocal PROC USES esi edi ebx exact_match

  local extsize_local, offset_local

	strlen( __outpath )
	mov	edi,eax
	xor	eax,eax
	xor	esi,esi
	mov	extsize_local,eax
	dec	eax
	mov	offset_local,eax
lupe:
	mov	eax,SIZE S_ZEND
	call	oread
	mov	ebx,eax
	jz	error
	cmp	WORD PTR [ebx],ZIPHEADERID
	jne	error
	mov	eax,esi
	cmp	WORD PTR [ebx+2],ZIPLOCALID
	jne	toend
	lea	eax,[edi+SIZE S_LZIP]
@@:
	call	oread
	mov	ebx,eax
	jz	error
	mov	eax,SIZE S_LZIP
	add	ax,[ebx].S_LZIP.lz_fnsize
	cmp	ecx,eax
	jb	@B
	add	ax,[ebx].S_LZIP.lz_extsize
	add	eax,[ebx].S_LZIP.lz_csize
	push	eax
	test	esi,esi
	jnz	copy
	movzx	eax,[ebx].S_LZIP.lz_fnsize
	cmp	exact_match,esi
	je	subdir
	cmp	edi,eax
	je	compare
copy:
	xor	edx,edx
	pop	eax
	iocopy( addr STDO, addr STDI, edx::eax )
	jz	error
	jmp	lupe
subdir:
	cmp	eax,edi
	jbe	copy
compare:
	_strnicmp( __outpath, addr [ebx+SIZE S_LZIP], edi )
	jnz	copy
	inc	esi
	movzx	eax,[ebx].S_LZIP.lz_extsize
	mov	extsize_local,eax
	mov	ax,[ebx].S_LZIP.lz_fnsize
	push	eax
	add	ebx,SIZE S_LZIP
	and	eax,01FFh
	memcpy( entryname, ebx, eax )
	pop	ebx
	add	ebx,eax
	mov	BYTE PTR [ebx],0
	mov	eax,DWORD PTR STDO.ios_total
	add	eax,STDO.ios_i
	mov	offset_local,eax
	pop	ecx
	add	eax,ecx
	oseek ( eax, SEEK_SET )
	jnz	lupe
	mov	eax,-1
toend:
	mov	edx,offset_local
	mov	ecx,extsize_local
	ret
error:
	mov	eax,-1
	jmp	toend
zip_copylocal ENDP

zip_copycentral PROC USES esi edi ebx loffset, lsize, exact_match
	strlen( __outpath )
	mov	edi,eax
	xor	esi,esi
lupe:
	mov	eax,SIZE S_ZEND
	call	oread
	mov	ebx,eax
	jz	error
	cmp	[ebx].S_CZIP.cz_pkzip,ZIPHEADERID	; 'PK'	4B50h
	jne	error
	cmp	[ebx].S_CZIP.cz_zipid,ZIPCENTRALID	; 1,2	0201h
	jne	toend
	mov	eax,SIZE S_CZIP
	call	oread
	mov	ebx,eax
	jz	error
	mov	eax,SIZE S_CZIP
	add	ax,[ebx].S_CZIP.cz_fnsize
	call	oread
	mov	ebx,eax
	jz	error
	mov	eax,SIZE S_CZIP			; Central directory
	add	ax,[ebx].S_CZIP.cz_fnsize	; file name length (*this)
	add	ax,[ebx].S_CZIP.cz_extsize
	add	ax,[ebx].S_CZIP.cz_cmtsize
	push	eax				; = size of this record
	mov	eax,loffset			; Update local offset if above
	cmp	[ebx].S_CZIP.cz_off_local,eax
	jb	@F
	mov	eax,lsize
	sub	[ebx].S_CZIP.cz_off_local,eax
@@:
	test	esi,esi
	jnz	copy				; already found -- deleted
	movzx	eax,[ebx].S_CZIP.cz_fnsize
	cmp	exact_match,0
	je	@F
	cmp	edi,eax
	jne	copy
@@:
	cmp	edi,eax
	ja	copy
	add	ebx,SIZE S_CZIP
	_strnicmp( __outpath, ebx, edi )
	test	eax,eax
	jz	delete
copy:
	pop	eax
	sub	edx,edx
	iocopy( addr STDO, addr STDI, edx::eax )
	jnz	lupe
	jmp	error
delete:
	pop	eax
	inc	esi
	oseek ( eax, SEEK_CUR )
	jnz	lupe
error:
	mov	esi,-1
toend:
	mov	eax,esi
	ret
zip_copycentral ENDP

zip_copyendcentral PROC USES esi edi
	mov	esi,eax
	mov	edi,edx
	mov	eax,dword ptr STDO.ios_total
	add	eax,STDO.ios_i
	sub	eax,zip_endcent.ze_off_cent
	mov	zip_endcent.ze_size_cent,eax
	mov	eax,SIZE S_ZEND
	call	oread
	jz	error
	memcpy( eax, addr zip_endcent, SIZE S_ZEND )
	xor	edx,edx
	movzx	eax,zip_endcent.ze_comment_size
	add	eax,SIZE S_ZEND
	iocopy( addr STDO, addr STDI, edx::eax )
	jz	error
	ioflush( addr STDO )
	jz	error
	mov	eax,DWORD PTR STDO.ios_total
	mov	zip_flength,eax
	call	zip_renametemp		; 0 or -1
toend:
	ret
error:
	dec	eax			; -1
	jmp	toend
zip_copyendcentral ENDP

	END
