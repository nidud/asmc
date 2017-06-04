include consx.inc
include string.inc
include wsub.inc
include iost.inc
include errno.inc
include zip.inc

	.data

externdef	IDD_UnzipCRCError:DWORD

key0		dd 0
key1		dd 0
key2		dd 0

password	db 80 dup(0)
enterpassword	db 'Enter password',0
format_sL_02X	db "%s",10,"'%02X'",0

	.code

	OPTION	PROC: PRIVATE

_CRC32	PROC
	xor	eax,edx
	and	eax,000000FFh
	mov	eax,crctab[eax*4]
	shr	edx,8
	xor	eax,edx
	ret
_CRC32	ENDP

update_keys PROC
	push	eax
	mov	edx,key0
	call	_CRC32
	mov	key0,eax
	and	eax,000000FFh
	add	eax,key1
	mov	edx,134775813
	mul	edx
	inc	eax
	mov	key1,eax
	mov	edx,key2
	shr	eax,24
	call	_CRC32
	mov	key2,eax
	pop	eax
	ret
update_keys ENDP

decryptbyte PROC
	push	ebx
	mov	ebx,key2
	or	ebx,2
	mov	edx,ebx
	xor	edx,1
	mov	eax,ebx
	mul	edx
	mov	al,ah
	pop	ebx
	ret
decryptbyte ENDP

init_keys PROC
	mov	key0,12345678h
	mov	key1,23456789h
	mov	key2,34567890h
	push	esi
	mov	esi,offset password
@@:
	movzx	eax,byte ptr [esi]
	inc	esi
	test	eax,eax
	jz	@F
	call	update_keys
	jmp	@B
@@:
	pop	esi
	ret
init_keys ENDP

decrypt PROC
	push	esi
	push	ebx
	xor	esi,esi
@@:
	call	decryptbyte
	mov	ebx,STDI.S_IOST.ios_bp
	add	ebx,esi
	xor	[ebx],al
	mov	al,[ebx]
	call	update_keys
	inc	esi
	cmp	esi,STDI.S_IOST.ios_c
	jl	@B
	pop	ebx
	pop	esi
	ret
decrypt ENDP

test_password PROC USES esi edi string

  local b[12]:BYTE

	call	init_keys
	lea	edi,b
	memcpy( edi, string, 12 )
	xor	esi,esi
@@:
	call	decryptbyte
	xor	[edi],al
	mov	al,[edi]
	call	update_keys
	inc	edi
	inc	esi
	cmp	esi,12
	jne	@B
	lea	edi,b
	mov	ax,zip_local.lz_time
	test	zip_attrib,_FB_ZEXTLOCHD
	jnz	@F
	mov	ax,WORD PTR zip_local.lz_crc[2]
@@:
	cmp	ah,[edi+11]
	je	@F
	xor	eax,eax
	jmp	toend
@@:
	mov	ecx,STDI.S_IOST.ios_c
	sub	ecx,12
	mov	esi,STDI.S_IOST.ios_bp
	add	esi,12
@@:
	call	decryptbyte
	xor	[esi],al
	mov	al,[esi]
	call	update_keys
	inc	esi
	dec	ecx
	jnz	@B
	xor	eax,eax
	inc	eax
toend:
	ret
test_password ENDP

zip_decrypt PROC USES esi edi

  local b[12]:BYTE

	mov	esi,12
	lea	edi,b
@@:
	call	ogetc
	mov	[edi],al
	inc	edi
	dec	esi
	jnz	@B
	test_password( addr b )
	test	eax,eax
	jnz	@F
	mov	password,al
	tgetline( addr enterpassword, addr password, 32, 80 )
	test	eax,eax
	jz	@F
	xor	eax,eax
	cmp	password,al
	je	@F
	test_password( addr b )
@@:
	test eax,eax
	ret
zip_decrypt ENDP

	OPTION	PROC: PUBLIC

zip_unzip PROC
	push	esi
	mov	esi,ER_MEM
	mov	STDI.ios_file,eax	; zip file handle
	mov	STDO.ios_file,edx	; out file handle
	ioinit( addr STDO, WSIZE )
	jz	mem_error
	ioinit( addr STDI, OO_MEM64K )
	jz	mem_error2
	mov	esi,-1
	or	STDO.ios_flag,IO_UPDTOTAL or IO_USEUPD or IO_USECRC
	test	zip_attrib,_FB_ZENCRYPTED
	jz	method
	call	ogetc
	jz	done
	dec	STDI.ios_i
	call	zip_decrypt
	test	eax,eax
	jz	done
	or	STDI.ios_flag,IO_CRYPT
method:
	sub	eax,eax
	or	ax,zip_local.lz_method
	jz	store
	cmp	eax,8
	je	inflate
	cmp	eax,6
	je	explode
	jmp	method_error
store:
	or	STDI.ios_flag,IO_USECRC
	sub	edx,edx
	mov	eax,zip_local.lz_fsize
	iocopy( addr STDO, addr STDI, edx::eax )
	mov	esi,eax
	ioflush( addr STDO )
	dec	esi
	jmp	done
explode:
	call	zip_explode
	mov	esi,eax
	jmp	done
inflate:
	call	zip_inflate
	mov	esi,eax
done:
	iofree( addr STDI )
mem_error2:
	iofree( addr STDO )
mem_error:
	test	STDO.ios_flag,IO_ERROR
	jz	@F
	mov	esi,ER_DISK
@@:
	test	esi,esi
	jnz	toend
	mov	eax,STDO.ios_crc
	not	eax
	cmp	eax,zip_local.lz_crc
	je	toend
	rsmodal( IDD_UnzipCRCError )
	jnz	toend
	mov	esi,ER_CRCERR
toend:
	mov	eax,esi
	pop	esi
	ret
method_error:
	ermsg(	addr cp_warning,
		addr format_sL_02X,
		zip_local.lz_method,
		sys_errlist[ENOSYS*4] )
	mov	esi,ERROR_INVALID_FUNCTION
	jmp	toend
zip_unzip ENDP

	END
