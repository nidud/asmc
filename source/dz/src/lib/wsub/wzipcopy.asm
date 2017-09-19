include direct.inc
include io.inc
include iost.inc
include alloc.inc
include string.inc
include wsub.inc
include zip.inc
include filter.inc
include consx.inc
include progress.inc
include errno.inc
include syserrls.inc

setftime	PROTO :SINT, :DWORD
externdef	cp_emarchive:BYTE
externdef	cp_emaxfb:BYTE

DC_MAXOBJ	equ 5000 ; Max number of files in one subdir (recursive)

S_ZSUB		STRUC
zs_wsub		S_WSUB <>
zs_index	dd ?
zs_result	dd ?
S_ZSUB		ENDS

	.code

	OPTION	PROC: PRIVATE

wzipfindentry PROC USES esi edi fblk, ziph
	mov	esi,ziph
	mov	edi,fblk
	strlen( addr [edi].S_FBLK.fb_name )
	add	eax,SIZE S_FBLK
	add	edi,eax
	_lseek( esi,[edi],SEEK_SET )
	osread( esi, addr zip_local, SIZE S_LZIP )
	cmp	eax,SIZE S_LZIP
	jne	error
	cmp	zip_local.lz_pkzip,ZIPHEADERID
	jne	error
	cmp	zip_local.lz_zipid,ZIPLOCALID
	jne	error
	mov	ax,zip_local.lz_fnsize
	add	ax,zip_local.lz_extsize
	_lseek( esi, eax, SEEK_CUR )
	test	zip_local.lz_flag,8
	jz	@F
	mov	eax,fblk
	mov	eax,[edi+4]
	mov	zip_local.lz_crc,eax
	mov	eax,[edi+8]
	mov	zip_local.lz_csize,eax
@@:
	mov	eax,1
toend:
	test	eax,eax
	ret
error:
	xor	eax,eax
	jmp	toend
wzipfindentry ENDP

wzipcopyfile PROC USES esi edi ebx wsub, fblk, out_path

  local fhandle:DWORD, fname[_MAX_PATH*2]:BYTE

	mov	ebx,fblk
	filter_fblk( ebx )
	test	eax,eax
	jz	toend

	wsopenarch( wsub )
	cmp	eax,-1
	je	ernozip

	mov	esi,eax
	wzipfindentry( ebx, esi )
	jz	erfind

	lea	edi,fname
	strfcat( edi, out_path, addr [ebx].S_FBLK.fb_name )
	progress_set( addr [ebx].S_FBLK.fb_name, out_path, [ebx].S_FBLK.fb_size )
	test	eax,eax
	jnz	eruser

	ogetouth( edi, M_WRONLY )
	cmp	eax,0
	jle	eruser

	mov	fhandle,eax
	mov	edx,eax
	mov	eax,[ebx].S_FBLK.fb_flag
	mov	zip_attrib,eax
	mov	eax,esi
	call	zip_unzip
	push	eax
	_close( esi )
	pop	eax
	test	eax,eax
	jnz	@F

	setftime( fhandle, [ebx].S_FBLK.fb_time )
	_close( fhandle )
	mov	eax,[ebx].S_FBLK.fb_flag
	and	eax,_A_FATTRIB
	setfattr( edi, eax )
	xor	eax,eax
	jmp	toend
@@:
	_close( fhandle )
	push	eax
	remove( edi )
	pop	eax
	cmp	eax,ER_USERABORT
	je	toend
	cmp	eax,ERROR_INVALID_FUNCTION
	je	toend
	mov	esi,eax
	mov	edx,offset CP_ENOMEM
	cmp	eax,ER_MEM
	jne	@F
	mov	eax,edx
	jmp	error
@@:
	cmp	eax,ER_DISK
	jne	@F
	mov	eax,offset CP_ENOSPC
	jmp	error
@@:
	mov	edx,offset CP_EIO
	mov	eax,offset cp_emarchive
	mov	ecx,errno
	test	ecx,ecx
	jz	error
	mov	edx,sys_errlist[ecx*4]
error:
	ermsg ( eax, "%s\n\n%s", edi, edx )
	mov	eax,esi
toend:
	ret
ernozip:
	mov	eax,ER_NOZIP
	jmp	toend
erfind:
	add	ebx,S_FBLK.fb_name
	ermsg ( addr CP_ENOENT, ebx )
	mov	eax,ER_FIND
eruser:
	push	eax
	_close( esi )
	pop	eax
	jmp	toend
wzipcopyfile ENDP

wzipcopypath PROC PRIVATE USES esi edi ebx wsub, fblk, out_path

  local zs:S_ZSUB

	mov	esi,wsub
	lea	edi,zs.zs_wsub
	mov	zs.zs_wsub.ws_flag,_W_SORTSIZE ;or _W_MALLOC
	mov	zs.zs_wsub.ws_maxfb,DC_MAXOBJ
	wsopen( edi )
	test	eax,eax
	jz	error
	mov	ebx,[edi].S_WSUB.ws_path
	mov	eax,[esi].S_WSUB.ws_path
	mov	[edi].S_WSUB.ws_path,eax
	mov	eax,[esi].S_WSUB.ws_file
	mov	[edi].S_WSUB.ws_file,eax
	mov	eax,[esi].S_WSUB.ws_mask
	mov	[edi].S_WSUB.ws_mask,eax
	lea	edx,[ebx+WMAXPATH]
	mov	[edi].S_WSUB.ws_arch,edx
	mov	eax,fblk
	lea	eax,[eax].S_FBLK.fb_name
	mov	ecx,[esi].S_WSUB.ws_arch
	cmp	BYTE PTR [ecx],0
	je	@F
	strfcat( edx, ecx, eax )
	jmp	l1
@@:
	strcpy( edx, eax )
l1:
	mov	esi,ebx
	mov	ebx,fblk
	strfcat( esi, out_path, addr [ebx].S_FBLK.fb_name )
	_mkdir ( esi )
	cmp	eax,-1
	je	@F
	setfattr( esi, 0 )
	test	eax,eax
	jnz	@F
	mov	eax,fblk
	mov	eax,[eax].S_FBLK.fb_flag
	and	eax,_A_FATTRIB
	and	eax,not _A_SUBDIR
	setfattr( esi, eax )
@@:
	progress_set( addr [ebx].S_FBLK.fb_name, out_path, 0 )
	jnz	toend
	wzipread( edi )
	cmp	eax,1
	ja	sort
	mov	[edi].S_WSUB.ws_path,esi
	wsclose( edi )
	xor	eax,eax
toend:
	ret
error:
	mov	eax,-1
	jmp	toend
warning:
	stdmsg( addr cp_warning, addr cp_emaxfb, eax, eax )
	jmp	max
sort:
	wssort( edi )
	mov	eax,[edi].S_WSUB.ws_maxfb
	cmp	eax,[edi].S_WSUB.ws_count
	je	warning
max:
	mov	eax,[edi].S_WSUB.ws_count
	dec	eax
	mov	zs.zs_index,eax
	xor	eax,eax
	mov	zs.zs_result,eax
next:
	cmp	BYTE PTR zs.zs_result,0
	jne	closews
	mov	eax,zs.zs_index
	cmp	eax,1
	jl	closews
	mov	ebx,[edi].S_WSUB.ws_fcb
	mov	ebx,[ebx+eax*4]
	mov	eax,[ebx].S_FBLK.fb_flag
	and	eax,_A_SUBDIR
	jz	file
	wzipcopypath( edi, ebx, esi )
	mov	zs.zs_result,eax
	jmp	freews
closews:
	mov	[edi].S_WSUB.ws_path,esi
	wsclose( edi )
	mov	eax,zs.zs_result
	jmp	toend
file:
	push	edx
	push	ebx
	progress_set( addr [ebx].S_FBLK.fb_name, out_path, [ebx].S_FBLK.fb_size )
	mov	zs.zs_result,eax
	pop	ebx
	pop	edx
	jnz	closews
	wzipcopyfile( edi, ebx, esi )
	mov	zs.zs_result,eax
freews:
	mov	ebx,[edi].S_WSUB.ws_fcb
	mov	eax,zs.zs_index
	lea	ebx,[ebx+eax*4]
	xor	eax,eax
	push	[ebx]
	mov	[ebx],eax
	call	free
	dec	zs.zs_index
	jmp	next
wzipcopypath ENDP

	OPTION	PROC: PUBLIC

wzipcopy PROC wsub, fblk, out_path
	mov	eax,fblk
	push	out_path
	push	eax
	push	wsub

	test	BYTE PTR [eax].S_FBLK.fb_flag,_A_SUBDIR
	jnz	subdir
	call	wzipcopyfile
toend:
	ret
subdir:
	call	wzipcopypath
	jmp	toend
wzipcopy ENDP

	END
