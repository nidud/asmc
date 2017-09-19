include consx.inc
include string.inc
include wsub.inc
include iost.inc
include errno.inc
include zip.inc

    .data

extern   IDD_UnzipCRCError:dword

key0     dd 0
key1     dd 0
key2     dd 0
password db 80 dup(0)

    .code

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
    or  ebx,2
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
            or  STDO.ios_flag,IO_UPDTOTAL or IO_USEUPD or IO_USECRC
            .repeat
                .if zip_attrib & _FB_ZENCRYPTED
                    ogetc()
                    .break .ifz
                    dec STDI.ios_i
                    .break .if !zip_decrypt()
                    or  STDI.ios_flag,IO_CRYPT
                .endif
                sub eax,eax
                or  ax,zip_local.lz_method
                .ifz
                    or  STDI.ios_flag,IO_USECRC
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
                        zip_local.lz_method, sys_errlist[ENOSYS*4])
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

    END
