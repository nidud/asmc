include io.inc
include string.inc
include errno.inc
include time.inc
include iost.inc
include wsub.inc
include zip.inc
include consx.inc
include dzlib.inc

extern IDD_UnzipCRCError:dword

    .data
    zip_attrib	dd 0
    zip_flength dd 0
    zip_local	S_LZIP <0>
    zip_central S_CZIP <0>
    zip_endcent S_ZEND <0,0,0,0,0,0,0,0>

    key0     dd 0
    key1     dd 0
    key2     dd 0
    password db 80 dup(0)

    .code

zip_renametemp proc
    ioclose(&STDI)
    ioclose(&STDO)
    filexist(edi)	    ; 1 file, 2 subdir
    dec eax
    .ifz
	remove(esi)
	rename(edi, esi)   ; 0 or -1
    .else
	mov eax,-1
    .endif
    ret
zip_renametemp endp

    option proc:private

_CRC32 proc
    xor eax,edx
    and eax,000000FFh
    mov eax,crctab[eax*4]
    shr edx,8
    xor eax,edx
    ret
_CRC32 endp

update_keys proc
    push eax
    mov edx,key0
    _CRC32()
    mov key0,eax
    and eax,000000FFh
    add eax,key1
    mov edx,134775813
    mul edx
    inc eax
    mov key1,eax
    mov edx,key2
    shr eax,24
    _CRC32()
    mov key2,eax
    pop eax
    ret
update_keys endp

decryptbyte proc
    push ebx
    mov ebx,key2
    or	ebx,2
    mov edx,ebx
    xor edx,1
    mov eax,ebx
    mul edx
    mov al,ah
    pop ebx
    ret
decryptbyte endp

init_keys proc uses esi
    mov key0,12345678h
    mov key1,23456789h
    mov key2,34567890h
    mov esi,offset password
    .while 1
	movzx eax,byte ptr [esi]
	inc esi
	.break .if !eax
	update_keys()
    .endw
    ret
init_keys endp

decrypt proc uses esi ebx
    xor esi,esi
    .repeat
	decryptbyte()
	mov ebx,STDI.S_IOST.ios_bp
	add ebx,esi
	xor [ebx],al
	mov al,[ebx]
	update_keys()
	inc esi
    .until esi == STDI.S_IOST.ios_c
    ret
decrypt endp

test_password proc uses esi edi string

  local b[12]:byte

    init_keys()
    lea edi,b
    memcpy(edi, string, 12)
    xor esi,esi
    .repeat
	decryptbyte()
	xor [edi],al
	mov al,[edi]
	update_keys()
	inc edi
	inc esi
    .until esi == 12
    lea edi,b
    mov ax,zip_local.lz_time
    .if !(zip_attrib & _FB_ZEXTLOCHD)
	mov ax,word ptr zip_local.lz_crc[2]
    .endif
    .if ah != [edi+11]
	xor eax,eax
    .else
	mov ecx,STDI.S_IOST.ios_c
	sub ecx,12
	mov esi,STDI.S_IOST.ios_bp
	add esi,12
	.repeat
	    decryptbyte()
	    xor [esi],al
	    mov al,[esi]
	    update_keys()
	    inc esi
	.untilcxz
	xor eax,eax
	inc eax
    .endif
toend:
    ret
test_password endp

zip_decrypt proc uses esi edi

  local b[12]:byte

    mov esi,12
    lea edi,b
    .repeat
	ogetc()
	stosb
	dec esi
    .untilz
    .if !test_password(&b)
	mov password,al
	.if tgetline("Enter password", &password, 32, 80)
	    xor eax,eax
	    .if password != al
		test_password(&b)
	    .endif
	.endif
    .endif
    test eax,eax
    ret

zip_decrypt endp

    option proc:PUBLIC

zip_unzip proc uses esi

    mov esi,ER_MEM
    mov STDI.ios_file,eax   ; zip file handle
    mov STDO.ios_file,edx   ; out file handle

    .repeat
	.repeat
	    ioinit(&STDO, WSIZE)
	    .break .ifz
	    ioinit(&STDI, OO_MEM64K)
	    .ifz
		iofree(&STDO)
		.break
	    .endif
	    mov esi,-1
	    or	STDO.ios_flag,IO_UPDTOTAL or IO_USEUPD or IO_USECRC
	    .repeat
		.if zip_attrib & _FB_ZENCRYPTED
		    ogetc()
		    .break .ifz
		    dec STDI.ios_i
		    .break .if !zip_decrypt()
		    or	STDI.ios_flag,IO_CRYPT
		.endif
		sub eax,eax
		or  ax,zip_local.lz_method
		.ifz
		    or	STDI.ios_flag,IO_USECRC
		    sub edx,edx
		    mov eax,zip_local.lz_fsize
		    iocopy(&STDO, &STDI, edx::eax)
		    mov esi,eax
		    ioflush(&STDO)
		    dec esi
		.elseif eax == 8
		    zip_inflate()
		    mov esi,eax
		.elseif eax == 6
		    zip_explode()
		    mov esi,eax
		.else
		    ermsg(&cp_warning, "%s\n'%02X'",
			_sys_errlist[ENOSYS*4], zip_local.lz_method)
		    mov esi,ERROR_INVALID_FUNCTION
		    .break(2)
		.endif
	    .until 1
	    iofree(&STDI)
	    iofree(&STDO)
	.until 1
	.if STDO.ios_flag & IO_ERROR
	    mov esi,ER_DISK
	.endif
	.break .if esi
	mov eax,STDO.ios_crc
	not eax
	.break .if eax == zip_local.lz_crc
	.break .if rsmodal(IDD_UnzipCRCError)
	mov esi,ER_CRCERR
    .until 1
    mov eax,esi
    ret

zip_unzip endp

zip_copylocal PROC USES esi edi ebx exact_match

  local extsize_local, offset_local

    strlen( __outpath )
    mov edi,eax
    xor eax,eax
    xor esi,esi
    mov extsize_local,eax
    dec eax
    mov offset_local,eax
lupe:
    mov eax,sizeof(S_ZEND)
    call    oread
    mov ebx,eax
    jz	error
    cmp WORD PTR [ebx],ZIPHEADERID
    jne error
    mov eax,esi
    cmp WORD PTR [ebx+2],ZIPLOCALID
    jne toend
    lea eax,[edi+sizeof(S_LZIP)]
@@:
    call    oread
    mov ebx,eax
    jz	error
    mov eax,sizeof(S_LZIP)
    add ax,[ebx].S_LZIP.lz_fnsize
    cmp ecx,eax
    jb	@B
    add ax,[ebx].S_LZIP.lz_extsize
    add eax,[ebx].S_LZIP.lz_csize
    push    eax
    test    esi,esi
    jnz copy
    movzx   eax,[ebx].S_LZIP.lz_fnsize
    cmp exact_match,esi
    je	subdir
    cmp edi,eax
    je	compare
copy:
    xor edx,edx
    pop eax
    iocopy( addr STDO, addr STDI, edx::eax )
    jz	error
    jmp lupe
subdir:
    cmp eax,edi
    jbe copy
compare:
    _strnicmp( __outpath, addr [ebx+sizeof(S_LZIP)], edi )
    jnz copy
    inc esi
    movzx   eax,[ebx].S_LZIP.lz_extsize
    mov extsize_local,eax
    mov ax,[ebx].S_LZIP.lz_fnsize
    push    eax
    add ebx,sizeof(S_LZIP)
    and eax,01FFh
    memcpy( entryname, ebx, eax )
    pop ebx
    add ebx,eax
    mov BYTE PTR [ebx],0
    mov eax,DWORD PTR STDO.ios_total
    add eax,STDO.ios_i
    mov offset_local,eax
    pop ecx
    add eax,ecx
    oseek ( eax, SEEK_SET )
    jnz lupe
    mov eax,-1
toend:
    mov edx,offset_local
    mov ecx,extsize_local
    ret
error:
    mov eax,-1
    jmp toend
zip_copylocal ENDP

zip_copycentral PROC USES esi edi ebx loffset, lsize, exact_match
    strlen( __outpath )
    mov edi,eax
    xor esi,esi
lupe:
    mov eax,sizeof(S_ZEND)
    call    oread
    mov ebx,eax
    jz	error
    cmp [ebx].S_CZIP.cz_pkzip,ZIPHEADERID   ; 'PK'  4B50h
    jne error
    cmp [ebx].S_CZIP.cz_zipid,ZIPCENTRALID  ; 1,2   0201h
    jne toend
    mov eax,sizeof(S_CZIP)
    call    oread
    mov ebx,eax
    jz	error
    mov eax,sizeof(S_CZIP)
    add ax,[ebx].S_CZIP.cz_fnsize
    call    oread
    mov ebx,eax
    jz	error
    mov eax,sizeof(S_CZIP)	; Central directory
    add ax,[ebx].S_CZIP.cz_fnsize   ; file name length (*this)
    add ax,[ebx].S_CZIP.cz_extsize
    add ax,[ebx].S_CZIP.cz_cmtsize
    push    eax		    ; = size of this record
    mov eax,loffset	    ; Update local offset if above
    cmp [ebx].S_CZIP.cz_off_local,eax
    jb	@F
    mov eax,lsize
    sub [ebx].S_CZIP.cz_off_local,eax
@@:
    test    esi,esi
    jnz copy		    ; already found -- deleted
    movzx   eax,[ebx].S_CZIP.cz_fnsize
    cmp exact_match,0
    je	@F
    cmp edi,eax
    jne copy
@@:
    cmp edi,eax
    ja	copy
    add ebx,sizeof(S_CZIP)
    _strnicmp( __outpath, ebx, edi )
    test    eax,eax
    jz	delete
copy:
    pop eax
    sub edx,edx
    iocopy( addr STDO, addr STDI, edx::eax )
    jnz lupe
    jmp error
delete:
    pop eax
    inc esi
    oseek ( eax, SEEK_CUR )
    jnz lupe
error:
    mov esi,-1
toend:
    mov eax,esi
    ret
zip_copycentral ENDP

zip_copyendcentral PROC USES esi edi
    mov esi,eax
    mov edi,edx
    mov eax,dword ptr STDO.ios_total
    add eax,STDO.ios_i
    sub eax,zip_endcent.ze_off_cent
    mov zip_endcent.ze_size_cent,eax
    mov eax,S_ZEND
    oread()
    jz	error
    memcpy( eax, addr zip_endcent, S_ZEND )
    xor edx,edx
    movzx   eax,zip_endcent.ze_comment_size
    add eax,S_ZEND
    iocopy( addr STDO, addr STDI, edx::eax )
    jz	error
    ioflush( addr STDO )
    jz	error
    mov eax,DWORD PTR STDO.ios_total
    mov zip_flength,eax
    zip_renametemp()	; 0 or -1
toend:
    ret
error:
    or	eax,-1
    jmp toend
zip_copyendcentral ENDP


wsmkzipdir proc wsub, directory

    mov edx,wsub
    mov eax,__srcfile
    mov byte ptr [eax],0

    strfcat(__outfile, [edx].S_WSUB.ws_path, [edx].S_WSUB.ws_file)
    mov edx,wsub
    strfcat(__outpath, [edx].S_WSUB.ws_arch, directory)
    dostounix(strcat(eax, "/"))
    wzipadd(0, clock(), _A_SUBDIR)
    ret

wsmkzipdir endp

wsopenarch proc wsub:ptr S_WSUB

  local arcname[1024]:byte

    mov edx,wsub
    .if osopen(
	strfcat(
	    &arcname,
	    [edx].S_WSUB.ws_path,
	    [edx].S_WSUB.ws_file),
	_A_ARCH,
	M_RDONLY, A_OPEN) == -1
	eropen(&arcname)
    .endif
    ret

wsopenarch endp

    END
