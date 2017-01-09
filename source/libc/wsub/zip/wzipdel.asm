include string.inc
include wsub.inc
include iost.inc
include zip.inc
include confirm.inc
include progress.inc
include errno.inc

externdef	cp_ziptemp:BYTE

	.code

wzipdel PROC USES ebp esi edi

	mov	ebp,eax		; EAX --> EBP = wsub
	mov	edi,edx		; EDX --> EDI = fblk
	xor	eax,eax

lupe:
	mov	esi,eax
	test	eax,eax		; EAX set if repeated call with same directory
	mov	eax,entryname
	jnz	progress
	mov	ecx,[edi].S_FBLK.fb_flag
	lea	eax,[edi].S_FBLK.fb_name
	.if	cl & _A_SUBDIR
		confirm_delete_sub( eax )
	.else
		confirm_delete_file( eax, ecx )
	.endif

	test	eax,eax
	jz	toend			; 0: Skip file
	inc	eax
	jz	cancel			; -1: Cancel

	strfcat( __srcfile, [ebp].S_WSUB.ws_path, [ebp].S_WSUB.ws_file )
	setfext( strcpy( __outfile, eax ), addr cp_ziptemp )
	strfcat( __outpath, [ebp].S_WSUB.ws_arch, addr [edi].S_FBLK.fb_name )
	dostounix( eax )

	.if	BYTE PTR [edi].S_FBLK.fb_flag & _A_SUBDIR
		strcat( eax, "/" )
	.endif
	strcmp( __srcfile, __outfile )
	test	eax,eax
	jz	error_2
	mov	eax,__outpath
progress:
	mov	edx,zip_flength
	xor	ecx,ecx
	progress_set( eax, __srcfile, ecx::edx )
	mov	eax,__srcfile
	mov	edx,__outfile
	call	wscopy_open
	cmp	eax,-1
	je	error_1
	and	STDO.ios_flag,IO_GLMEM
	or	STDO.ios_flag,IO_UPDTOTAL or IO_USEUPD
	test	eax,eax
	jz	error_0
	;
	; copy compressed data to temp file
	;
	; 0: match directory\*.*
	; 1: exact match -- file or directory/
	;
	xor	esi,1
	zip_copylocal( esi )
	;
	; local offset to Central directory in DX
	;
	inc	eax
	jz	error_0
	mov	eax,DWORD PTR STDO.ios_total
	add	eax,STDO.ios_i
	mov	ecx,zip_endcent.ze_off_cent
	mov	zip_endcent.ze_off_cent,eax
	sub	ecx,eax
	zip_copycentral( edx, ecx, esi )
	;
	; must be found..
	;
	dec	eax
	jnz	error_0
	;
	;-------- End Central Directory
	;
	dec	zip_endcent.ze_entry_dir
	dec	zip_endcent.ze_entry_cur
	mov	eax,__srcfile
	mov	edx,__outfile
	call	zip_copyendcentral
	inc	eax
	mov	eax,0
	jnz	error_1
error_0:
	ioclose( addr STDI )
	mov	eax,__outfile
	call	wscopy_remove
	mov	eax,esi
	.if	eax
		sub	eax,2
	.endif
	inc	eax
error_1:
	mov	dl,[edi]
	and	dl,_A_SUBDIR
	jnz	toend
	cmp	eax,1
	jne	toend
error_2:		; 2: ZIP file deleted (Ok)
	.if	!errno
		mov	errno,ENOENT
	.endif
	erdelete( __outpath )
	inc	eax
cancel:
	inc	eax
toend:			; 0: Jump/Ok/Continue
	test	eax,eax
	jnz	@F
	mov	ecx,[edi]
	test	ecx,_A_SUBDIR
	jz	@F
	inc	eax
	jmp	lupe
@@:
	test	eax,eax
	ret
wzipdel ENDP

	END
