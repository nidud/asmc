include string.inc
include wsub.inc
include iost.inc
include io.inc
include errno.inc
include progress.inc
include zip.inc
include consx.inc
include strlib.inc

PUBLIC	ocentral
PUBLIC	cp_emarchive
PUBLIC	cp_ziptemp

	.data

ocentral	S_IOST <>
cp_ziptemp	db '.$$$',0
cp_emarchive	db "Error in archive",0

	.code

zip_clearentry PROC
	memset( addr zip_local, 0, SIZE S_LZIP )
	memset( addr zip_central, 0, SIZE S_CZIP )
	mov	zip_local.lz_pkzip,ZIPHEADERID
	mov	zip_local.lz_zipid,ZIPLOCALID
	mov	BYTE PTR zip_local.lz_version,20
	mov	zip_central.cz_pkzip,ZIPHEADERID
	mov	zip_central.cz_zipid,ZIPCENTRALID
	mov	BYTE PTR zip_central.cz_version_made,20
	mov	BYTE PTR zip_central.cz_version_need,10
	ret
zip_clearentry ENDP

zip_mkarchivetmp PROC
	setfext( strcpy( eax, __outfile ), addr cp_ziptemp )
	ret
zip_mkarchivetmp ENDP

zip_setprogress PROC
	xor	ecx,ecx
	or	STDO.ios_flag,IO_USEUPD or IO_UPDTOTAL
	progress_set( __outfile, ebx, ecx::eax )
	ret
zip_setprogress ENDP

zip_displayerror PROC
	mov	eax,_sys_errlist[ENOSPC*4]
	mov	edx,_sys_errlist[ENOMEM*4]
	test	STDO.ios_flag,IO_ERROR
	jnz	@F
	mov	ecx,errno
	mov	eax,edx
	cmp	ecx,ENOMEM
	je	@F
	mov	eax,offset cp_emarchive
	mov	edx,_sys_errlist[EIO*4]
	test	ecx,ecx
	jz	@F
	mov	edx,_sys_errlist[ecx*4]
@@:
	ermsg ( edx, eax )
	ret
zip_displayerror ENDP

;
; This is the fast compression startup
;
; The stratagy is to have two buffered files open
; - one for the local directory (compressed data)
; - and one for the central directory
;

wzipopen PROC USES esi edi ebx

  local arch[384]:BYTE

	call	zip_clearentry
	mov	esi,entryname
	strcpy( esi, __outfile )	; the <archive>.zip file (read)
	lea	eax,arch
	mov	edi,eax
	call	zip_mkarchivetmp		; the <archive>.$$$ file (write) - 8M
	strcpy( strfn( esi ), "centtmp.$$$" )	; the <centtmp.$$$> file (write) - 1M
	wscopyopen(__outfile, edi)		; open <archive> and <temp> file
	inc	eax				; (-1) -> (0)
	jz	toend				; error open...
	dec	eax				; (1) --> (0)
	jnz	openc				; == cancel
toend:
	test	eax,eax
	ret
ioerror:
	ioclose( addr ocentral )
	remove( esi )
eopen:
	wscopyremove(edi)
	sub	eax,eax
	jmp	toend
openc:						; open the <centtmp.$$$> file
	ioopen( addr ocentral, esi, M_RDWR, 100000h )
	cmp	eax,1
	jl	eopen
	lea	ebx,arch			; init progress for copy...
	mov	eax,zip_flength
	call	zip_setprogress
	mov	eax,zip_endcent.ze_off_cent	; == size of compressed data to copy
	sub	edx,edx
	iocopy( addr STDO, addr STDI, edx::eax )
	jz	ioerror
	mov	eax,zip_endcent.ze_size_cent	; copy central directory
	sub	edx,edx
	iocopy( addr ocentral, addr STDI, edx::eax )
	jz	errcpy
	and	STDO.ios_flag,IO_GLMEM		; clear flag for compression
	ioclose( addr STDI )			; close <archive> file
	mov	eax,1
	jmp	toend
errcpy:
	jmp	ioerror
wzipopen ENDP

;
; This is called when the copy loop ends
;
wzipclose PROC USES esi edi ebx

  local arch[384]:BYTE

	mov	esi,eax				; result
	lea	eax,arch
	mov	edi,eax
	call	zip_mkarchivetmp		; problems ?
	test	esi,esi
	jnz	error_1				; then remove temp files
	iotell( addr ocentral )			; get size of central directory
	mov	zip_endcent.ze_size_cent,eax	; update end-central info
	lea	ebx,arch			; set progress for last copy
	call	zip_setprogress
	sub	eax,eax
	cmp	DWORD PTR ocentral.ios_total,eax
	je	@F
	ioflush( addr ocentral )		; flush the <ocentral.$$$> buffer
	ioseek( addr ocentral, 0, SEEK_SET )
	jmp	copyc
@@:
	mov	ecx,ocentral.ios_i
	mov	ocentral.ios_c,ecx
	mov	ocentral.ios_i,eax
copyc:
	mov	eax,zip_endcent.ze_size_cent
	xor	edx,edx
	iocopy( addr STDO, addr ocentral, edx::eax )
	jz	error_2
	iowrite( addr STDO, addr zip_endcent, SIZE S_ZEND )
	jz	error_2
	movzx	esi,zip_endcent.ze_comment_size
	test	esi,esi
	jz	@F
	_close( ocentral.ios_file )	; add zip-comment to the end
	openfile( __outfile, M_RDONLY, A_OPEN )
	mov	ocentral.ios_file,eax
	mov	ebx,eax
	inc	eax
	jz	error_2
	sub	eax,eax
	sub	eax,esi
	_lseek( ebx, eax, SEEK_END )
	inc	eax
	jz	error_2
	sub	eax,eax
	mov	ocentral.ios_c,eax
	mov	ocentral.ios_i,eax
	iocopy( addr STDO, addr ocentral, eax::esi )
	jz	error_2
@@:
	ioflush( addr STDO )		; flush the <achive>.$$$ buffer
	jz	error_2
	ioclose( addr ocentral )	; close files
	ioclose( addr STDO )
	mov	esi,__outfile
	filexist( edi )			; 1 file, 2 subdir
	cmp	eax,1
	jne	error_1
	remove( esi )			; remove the <archive>.zip file
	rename( edi, esi )		; rename <achive>.$$$ to <achive>.zip
toend:
	remove( entryname )		; remove the <centtmp.$$$> file
	ret
error_2:
	ioclose( addr ocentral )
error_1:
	wscopyremove(edi)
	call	zip_displayerror
	jmp	toend
wzipclose ENDP

	END
