include string.inc
include wsub.inc
include iost.inc
include io.inc
include confirm.inc
include errno.inc
include zip.inc
include progress.inc

USE_DEFLATE	equ 1

externdef	compresslevel:DWORD
externdef	file_method:BYTE
externdef	copy_fast:BYTE
externdef	ocentral:S_IOST

	.code

	OPTION	PROC: PRIVATE

cmpmm	macro	des,src
	mov	eax,des
	cmp	eax,src
	endm

update_local PROC
	mov	eax,zip_central.cz_off_local
	cmp	eax,DWORD PTR STDO.ios_total
	jb	@F
	sub	eax,DWORD PTR STDO.ios_total
	add	eax,STDO.ios_bp
	memcpy( eax, addr zip_local, SIZE S_LZIP )
	ret
@@:
	ioflush( addr STDO )
	jz	@F
	_lseek( STDO.ios_file, zip_central.cz_off_local, SEEK_SET )
	oswrite( STDO.ios_file, addr zip_local, SIZE S_LZIP )
	_lseek( STDO.ios_file, 0, SEEK_END )
@@:
	ret
update_local ENDP

initentry PROC				; EAX	offset file name buffer
	push	eax			; BX	time
	mov	zip_local.lz_time,bx	; EDX	size
	mov	zip_central.cz_time,bx	; SI	attrib
	mov	zip_local.lz_date,di	; DI	date
	mov	zip_central.cz_date,di
	mov	eax,edx
	mov	zip_local.lz_fsize,eax
	mov	zip_local.lz_csize,eax
	mov	zip_central.cz_fsize,eax
	mov	zip_central.cz_csize,eax
	mov	eax,esi
	and	eax,_A_FATTRIB
	mov	zip_central.cz_ext_attrib,ax
	pop	eax
	strcpy( eax, __outpath )
	test	esi,_A_SUBDIR
	jnz	@F
	unixtodos( eax )
	push	eax
	strfn( __srcfile )
	pop	ecx
	strfcat( ecx, 0, eax )
	dostounix( eax )
@@:
	strlen( eax )
	mov	zip_local.lz_fnsize,ax
	mov	zip_central.cz_fnsize,ax
	ret
initentry ENDP

compress PROC
	cmp	zip_local.lz_fsize,2
	jb	@F
  if USE_DEFLATE
	cmp	compresslevel,0
	je	@F
	mov	STDI.ios_size,8000h
	zip_deflate( compresslevel )
	ret
  endif
@@:
	xor	edx,edx
	mov	eax,zip_local.lz_fsize
	iocopy( addr STDO, addr STDI, edx::eax )
	ret
compress ENDP

initcrc PROC
  if USE_DEFLATE
	movzx	eax,file_method
	mov	zip_local.lz_method,ax
	mov	zip_central.cz_method,ax
  endif
	mov	eax,STDI.ios_crc
	not	eax
	mov	zip_local.lz_crc,eax
	mov	zip_central.cz_crc,eax
	ioclose( addr STDI )
	ret
initcrc ENDP

popstdi PROC
	lea	eax,STDI
	memcpy( eax, esi, SIZE S_IOST )
	sub	eax,eax
	ret
popstdi ENDP

	OPTION	PROC: PUBLIC

wzipadd PROC USES esi edi ebx fsize:QWORD, ftime:DWORD, fattrib:DWORD

  local ios:S_IOST,
	ztemp[384]:BYTE,
	zpath[384]:BYTE,
	local_size:DWORD,
	result_copyl:DWORD,
	offset_local:DWORD,
	deflate_begin:DWORD

	movzx	edi,WORD PTR ftime+2
	mov	esi,fattrib
	xor	eax,eax
	mov	errno,eax
  if USE_DEFLATE
	mov	file_method,al
  endif
	;
	; Skip files > 4G...
	;
	cmp	eax,DWORD PTR fsize[4]
	jne	toend

	cmp	copy_fast,al
	je	slow

	lea	eax,zpath
	movzx	ebx,WORD PTR ftime
	mov	edx,DWORD PTR fsize
	call	initentry
	xor	eax,eax
	mov	zip_local.lz_crc,eax
	mov	zip_central.cz_crc,eax
	mov	zip_central.cz_off_local,eax
	test	esi,_A_SUBDIR
	jnz	subdir
	mov	eax,dword ptr STDO.ios_total
	add	eax,STDO.ios_i
	mov	zip_central.cz_off_local,eax
	ioopen( addr STDI, __srcfile, M_RDONLY, OO_MEM64K )
  if USE_DEFLATE
	mov	STDI.ios_size,8000h
  endif
	inc	eax
	jnz	@F
	;
	; v2.33 continue if error open source
	;
	jmp	toend
@@:
	iowrite( addr STDO, addr zip_local, SIZE S_LZIP )
	jz	error_2
	movzx	ecx,zip_local.lz_fnsize
	iowrite( addr STDO, addr zpath, ecx )
	jz	error_2
	or	STDI.ios_flag,IO_USECRC or IO_USEUPD or IO_UPDTOTAL
	mov	eax,dword ptr STDO.ios_total
	add	eax,STDO.ios_i
	mov	deflate_begin,eax
	call	compress
	test	eax,eax
	jz	error_2
	call	initcrc
subdir:
	mov	eax,dword ptr STDO.ios_total
	add	eax,STDO.ios_i
	mov	zip_endcent.ze_off_cent,eax
	test	BYTE PTR fattrib,_A_SUBDIR
	jnz	@F
	sub	eax,deflate_begin
	mov	zip_local.lz_csize,eax
	mov	zip_central.cz_csize,eax
	call	update_local
@@:
	iowrite( addr ocentral, addr zip_central, SIZE S_CZIP )
	jz	error_1
	iowrite( addr ocentral, addr zpath, zip_central.cz_fnsize )
	jz	error_1
	inc	zip_endcent.ze_entry_cur
	inc	zip_endcent.ze_entry_dir
	sub	eax,eax
	jmp	toend
    ;--------------------------------------------------------------
    ; do slow copy
    ;--------------------------------------------------------------
slow:
	mov	eax,zip_flength
	mov	DWORD PTR progress_size,eax
	mov	DWORD PTR progress_size[4],0
	call	zip_clearentry
	strcpy( addr zpath, __outpath )
	mov	eax,__outpath
	movzx	ebx,WORD PTR ftime
	mov	edx,DWORD PTR fsize
	call	initentry
	lea	eax,ztemp
	call	zip_mkarchivetmp
	wscopyopen(__outfile, eax)
	cmp	eax,-1
	jne	@F
	jmp	toend
@@:
	mov	eax,STDO.ios_flag
	and	eax,not IO_GLMEM
	or	eax,IO_USEUPD or IO_UPDTOTAL
	mov	STDO.ios_flag,eax
	test	eax,eax
	jnz	@F
	inc	eax
	jmp	toend
@@:
	xor	eax,eax
	mov	local_size,eax
	zip_copylocal( 1 )
	mov	result_copyl,eax	; result: 1 found, 0 not found, -1 error
	mov	offset_local,edx	; offset local directory if found
	mov	ecx,eax
	inc	eax
	jz	error_3
	mov	eax,dword ptr STDO.ios_total
	add	eax,STDO.ios_i
	mov	zip_central.cz_off_local,eax
@@:
	dec	ecx
	jnz	@F
	mov	ecx,zip_endcent.ze_off_cent
	sub	ecx,eax
	mov	local_size,ecx
@@:
	memcpy( addr ios, addr STDI, SIZE S_IOST )
	test	esi,_A_SUBDIR
	lea	esi,ios
	jnz	@F;wzipslow_subdir
  if USE_DEFLATE
	mov	file_method,0
  endif
	ioopen( addr STDI, __srcfile, M_RDONLY, OO_MEM64K )
  if USE_DEFLATE
	mov	STDI.ios_size,8000h
  endif
	cmp	eax,-1
	jne	@F
	call	popstdi
	;
	; v2.33 continue if error open source
	;
	jmp	skip
@@:
	iowrite( addr STDO, addr zip_local, SIZE S_LZIP )
	jz	ersource
	movzx	ecx,zip_local.lz_fnsize
	iowrite( addr STDO, __outpath, ecx )
	jz	ersource
	and	STDI.ios_flag,IO_GLMEM
	or	STDI.ios_flag,IO_USECRC or IO_USEUPD or IO_UPDTOTAL
	and	STDO.ios_flag,not IO_USEUPD
	mov	eax,dword ptr STDO.ios_total
	add	eax,STDO.ios_i
	mov	deflate_begin,eax
	progress_set( __srcfile, __outfile, fsize )
	jnz	ersource
	test	BYTE PTR fattrib,_A_SUBDIR
	jnz	subd
	call	compress
	test	eax,eax
	jnz	zerofile
ersource:
	ioclose( addr STDI )
	call	popstdi
	jmp	error_3
zerofile:
	call	initcrc
	call	popstdi
	lea	ebx,ztemp
	mov	eax,zip_flength
	call	zip_setprogress
subd:
	mov	eax,dword ptr STDO.ios_total
	add	eax,STDO.ios_i
	mov	zip_endcent.ze_off_cent,eax
	sub	eax,deflate_begin
	mov	zip_local.lz_csize,eax
	mov	zip_central.cz_csize,eax
	add	DWORD PTR progress_size,eax
	adc	DWORD PTR progress_size[4],0
	call	update_local
@@:
	zip_copycentral( offset_local, local_size, 1 )
	inc	eax
	jz	error_4
	dec	eax			; if file or directory deleted
	jz	@F			; -- ask user to overwrite
	dec	zip_endcent.ze_entry_dir
	dec	zip_endcent.ze_entry_cur
	confirm_delete_file( __outpath, zip_central.cz_ext_attrib )
	inc	eax
	jz	error_4			; Cancel (-1)
	dec	eax
	jz	skip			; Jump (0)
	jmp	czip
@@:
	cmp	result_copyl,eax
	jne	error_4			; found local, not central == error
czip:
	iowrite( addr STDO, addr zip_central, SIZE S_CZIP )
	jz	error_4
	movzx	ecx,zip_central.cz_fnsize
	iowrite( addr STDO, __outpath, ecx )
	jz	error_4
	inc	zip_endcent.ze_entry_cur
	inc	zip_endcent.ze_entry_dir
	mov	eax,__outfile
	lea	edx,ztemp
	call	zip_copyendcentral
	inc	eax
	jz	error_4
success:
	strcpy( __outpath, addr zpath )
	xor	eax,eax
toend:
	test	eax,eax
	ret
skip:
	ioclose( addr STDI )
	wscopyremove(addr ztemp)
	jmp	success
error_2:
	ioclose( addr STDI )
error_1:
	ioclose( addr STDO )
	ioclose( addr ocentral )
	remove( entryname )
	mov	eax,-1
	jmp	toend
error_4:
	xor	eax,eax
error_3:
	mov	edi,eax
	ioclose( addr STDI )
	wscopyremove(addr ztemp)
	mov	eax,edi
	inc	edi
	jz	toend
	call	zip_displayerror
	dec	eax
	jmp	toend
wzipadd ENDP

	END
