include io.inc
include malloc.inc
include stdio.inc
include string.inc
include errno.inc
include iost.inc
include consx.inc
include dzlib.inc
include confirm.inc

public STDI
public STDO
public oupdate
public odecrypt

    .data
    oupdate  dd 0
    odecrypt dd 0
    STDI S_IOST {0,0,0,0x8000,0,0,0,0,{0},{0},{0}}
    STDO S_IOST {0,0,0,0x8000,0,0,0,0,{0},{0},{0}}

    .code

ioinit proc uses edi io:ptr S_IOST, bsize

    mov edi,io
    mov edx,[edi].S_IOST.ios_file
    mov ecx,sizeof(S_IOST)
    xor eax,eax
    rep stosb
    mov edi,io

    mov [edi].S_IOST.ios_file,edx
    dec [edi].S_IOST.ios_crc    ; CRC to FFFFFFFFh
    mov eax,bsize

    .if eax == OO_MEM64K

        mov [edi].S_IOST.ios_size,eax
        _aligned_malloc(_SEGSIZE_, _SEGSIZE_)
    .else
        .if !eax

            mov eax,OO_MEM64K
        .endif
        mov [edi].S_IOST.ios_size,eax

        .if malloc(eax) && !bsize

            mov [edi].S_IOST.ios_bp,eax
            ioread(edi)
            _filelength([edi].S_IOST.ios_file)
            mov dword ptr [edi].S_IOST.ios_fsize,eax
            mov dword ptr [edi].S_IOST.ios_fsize[4],edx

            .if !edx && eax <= STDI.ios_c

                or [edi].S_IOST.ios_flag,IO_MEMBUF
            .endif
            mov eax,[edi].S_IOST.ios_bp
        .endif
    .endif

    mov [edi].S_IOST.ios_bp,eax
    test eax,eax
    ret

ioinit endp

ioopen proc uses esi iost:ptr S_IOST, file:LPSTR, mode, bsize

    .if mode == M_RDONLY

        openfile(file, mode, A_OPEN)
    .else
        ogetouth(file, mode)
    .endif

    .ifs eax > 0     ; -1, 0 (error, cancel), or handle

        mov esi,iost
        mov [esi].S_IOST.ios_file,eax
        .if !ioinit(esi, bsize)

            _close([esi].S_IOST.ios_file)
            ermsg(0, _sys_errlist[ENOMEM*4])
            xor eax,eax
        .else
            mov eax,[esi].S_IOST.ios_file
        .endif
    .endif
    ret

ioopen endp

iofree proc uses eax edx io:ptr S_IOST

    xor  eax,eax
    mov  ecx,io
    push [ecx].S_IOST.ios_bp
    mov  [ecx].S_IOST.ios_bp,eax
    pop  eax
    free(eax)
    ret

iofree endp

ioclose proc uses eax io:ptr S_IOST

    mov eax,io
    mov eax,[eax].S_IOST.ios_file
    .if eax != -1
        _close(eax)
    .endif
    iofree(io)
    ret

ioclose endp

    assume edx:ptr S_IOST

iotell proc io:ptr S_IOST

    mov edx,io
    mov eax,dword ptr [edx].ios_total
    add eax,[edx].ios_i
    mov edx,dword ptr [edx].ios_total[4]
    adc edx,0
    ret

iotell endp

ioseek proc uses esi iost:ptr S_IOST, offs:qword, from

    mov esi,iost
    mov eax,dword ptr offs
    mov edx,dword ptr offs[4]

    .repeat

        .if from == SEEK_CUR

            mov ecx,[esi].S_IOST.ios_c
            sub ecx,[esi].S_IOST.ios_i
            .if ecx >= eax
                add [esi].S_IOST.ios_i,eax
                test esi,esi
                .break
            .endif

        .elseif [esi].S_IOST.ios_flag & IO_MEMBUF

            .if eax > [esi].S_IOST.ios_c

                sub eax,eax
                mov eax,-1
                mov edx,eax
                .break
            .endif
            mov [esi].S_IOST.ios_i,eax
            mov dword ptr STDI.ios_offset,eax
            test esi,esi
            .break
        .endif

        .if _lseeki64([esi].S_IOST.ios_file, edx::eax, from) != -1
            mov dword ptr [esi].S_IOST.ios_offset,eax
            mov dword ptr [esi].S_IOST.ios_offset[4],edx
            sub ecx,ecx
            mov [esi].S_IOST.ios_i,ecx
            mov [esi].S_IOST.ios_c,ecx
            inc ecx
        .endif
    .until 1
    ret

ioseek endp

    assume ebx:ptr S_IOST

iocopy proc uses esi edi ebx ost:ptr S_IOST, ist:ptr S_IOST, len:qword

    xor eax,eax
    mov edx,ist
    mov ebx,ost
    mov esi,dword ptr len[4]
    mov edi,dword ptr len

    .repeat

        mov ecx,esi
        or  ecx,edi
        .ifz
            inc eax     ; copy zero byte is ok..
            .break
        .endif

        mov ecx,[edx].ios_c     ; if count is zero -- file copy
        sub ecx,[edx].ios_i
        .ifz
            mov eax,edx
            iogetc()
            .break .ifz
            dec [edx].ios_i
            mov ecx,[edx].ios_c
            sub ecx,[edx].ios_i
            .break .ifz
        .endif

        mov eax,[ebx].ios_size  ; copy max byte from STDI to STDO
        sub eax,[ebx].ios_i
        .if eax <= ecx
            mov ecx,eax
        .endif

        .if !esi && edi <= ecx
            mov ecx,edi
        .endif

        mov eax,ecx
        push esi
        push edi
        mov esi,[edx].ios_bp
        add esi,[edx].ios_i
        mov edi,[ebx].ios_bp
        add edi,[ebx].ios_i
        rep movsb
        pop edi
        pop esi

        add [ebx].ios_i,eax
        add [edx].ios_i,eax
        sub edi,eax
        sbb esi,0
        mov eax,edi
        or  eax,esi
        .ifz
            inc eax
            .break
        .endif

        mov eax,[edx].ios_c
        .if eax

            sub eax,[edx].ios_i ; flush inbuf
            .ifnz

                .repeat

                    mov eax,edx
                    iogetc()
                    .break(1) .ifz

                    mov edx,ebx
                    ioputc()
                    mov edx,ist
                    .break(1) .ifz

                    sub edi,eax
                    sbb esi,0
                    mov eax,esi
                    or  eax,edi
                    .ifz            ; success if zero (inbuf > len)
                        inc eax
                        .break(1)
                    .endif

                    mov eax,[edx].ios_i
                    ;
                    ; do byte copy from STDI to STDO
                    ;
                .until eax == [edx].ios_c
            .endif
        .endif

        ioflush(ebx)    ; flush STDO
        .break .ifz     ; do block copy of bytes left

        push [ebx].ios_size
        push [ebx].ios_bp
        mov eax,[edx].ios_bp
        mov [ebx].ios_bp,eax
        mov eax,[edx].ios_size
        mov [ebx].ios_size,eax

        .repeat

            ioread(edx)
            .ifz
                xor eax,eax
                .break .if esi
                .break .if edi
                inc eax
                .break
            .endif

            mov eax,[edx].ios_c     ; count
            .if !esi && eax >= edi
                mov eax,edi
                mov [edx].ios_i,eax
                mov [ebx].ios_i,eax
                ioflush(ebx)
                .break
            .endif

            sub edi,eax
            sbb esi,0
            mov [ebx].ios_i,eax     ; fill STDO
            mov [edx].ios_i,eax     ; flush STDI
            ioflush(ebx)            ; flush STDO
        .untilz                     ; copy next block

        pop ecx
        mov [ebx].ios_bp,ecx
        pop ecx
        mov [ebx].ios_size,ecx
    .until 1
    ret

iocopy endp

ioread proc uses esi edi ebx edx iost:ptr S_IOST

    mov ebx,iost
    mov esi,[ebx].ios_flag

    xor eax,eax
    .return .if esi & IO_MEMBUF

    mov edi,[ebx].ios_c
    sub edi,[ebx].ios_i

    .ifnz

        .return .if edi == [ebx].ios_c

        mov eax,[ebx].ios_bp
        add eax,[ebx].ios_i
        memcpy([ebx].ios_bp, eax, edi)
        xor eax,eax
    .endif

    mov [ebx].ios_i,eax
    mov [ebx].ios_c,edi

    mov ecx,[ebx].ios_size
    sub ecx,edi
    mov eax,[ebx].ios_bp
    add eax,edi
    osread([ebx].ios_file, eax, ecx)

    add [ebx].ios_c,eax
    add eax,edi
    .return .ifz

    and esi,IO_UPDTOTAL or IO_USECRC or IO_USEUPD or IO_CRYPT
    .ifz
        .return .if eax
    .endif

    .if esi & IO_CRYPT

        odecrypt()
    .endif

    .if esi & IO_UPDTOTAL

        add dword ptr [ebx].ios_total,eax
        adc dword ptr [ebx].ios_total[4],0
    .endif

    .if esi & IO_USECRC

        push eax
        add edi,[ebx].ios_bp

        .for ( ecx = [ebx].ios_crc, edx = 0 : eax : eax-- )

            mov dl,cl
            xor dl,[edi]
            shr ecx,8
            xor ecx,crctab[edx*4]
            inc edi
        .endf
        mov [ebx].ios_crc,ecx
        pop eax

    .endif

    .if esi & IO_USEUPD

        push eax
        push 0
        oupdate()
        dec eax
        pop eax

        .ifnz
            osmaperr()
            or [ebx].ios_flag,IO_ERROR
            xor eax,eax
        .endif
    .endif

    test eax,eax
    ret

ioread endp

iowrite proc uses esi edi ebx iost:ptr S_IOST, buf:PVOID, len

    mov esi,buf
    mov ebx,iost
    .repeat
        mov ecx,len
        mov edi,[ebx].ios_i
        mov eax,[ebx].ios_size
        sub eax,edi
        add edi,[ebx].ios_bp
        .if eax < ecx
            add [ebx].ios_i,eax
            sub len,eax
            mov ecx,eax
            rep movsb
            ioflush(ebx)
            .continue(0) .ifnz
            .break
        .endif
        add [ebx].ios_i,ecx
        rep movsb
    .until 1
    mov eax,esi
    ret

iowrite endp

    assume esi:ptr S_IOST

ioflush proc uses esi edi edx iost:ptr S_IOST

    mov esi,iost
    mov eax,[esi].ios_i

    .if eax

        .if [esi].ios_flag & IO_USECRC

            mov edi,[esi].ios_bp

            .for ( ecx = [esi].ios_crc, edx = 0 : eax : eax-- )

                mov dl,cl
                xor dl,[edi]
                shr ecx,8
                xor ecx,crctab[edx*4]
                inc edi
            .endf
            mov [esi].ios_crc,ecx

        .endif

        .if oswrite([esi].ios_file, [esi].ios_bp, [esi].ios_i) == [esi].ios_i

            add dword ptr [esi].ios_total,eax
            adc dword ptr [esi].ios_total[4],0
            xor eax,eax
            mov [esi].ios_c,eax
            mov [esi].ios_i,eax

            .if [esi].ios_flag & IO_USEUPD

                inc eax
                push eax
                oupdate()
                dec eax
            .endif
        .else
            or [esi].ios_flag,IO_ERROR
            or eax,-1
        .endif
    .endif

    inc eax
    ret

ioflush endp

ogetc proc

    lea eax,STDI

ogetc endp

iogetc proc uses edx

    mov edx,eax
    mov eax,[edx].ios_i

    .if eax == [edx].ios_c

        .while 1
            .if !([edx].ios_flag & IO_MEMBUF)
                push ecx
                ioread(edx)
                pop ecx
                mov eax,[edx].ios_i
                .break .ifnz
            .endif
            or  eax,-1
            xor edx,edx
            .return
        .endw
    .endif

    inc   [edx].ios_i
    add   eax,[edx].ios_bp
    movzx eax,byte ptr [eax]
    ret

iogetc endp

ioputc proc uses edx ecx

    mov ecx,[edx].ios_i

    .if ecx == [edx].ios_size

        push eax

        ioflush(edx)

        pop  eax

        .return 0 .ifz

        mov ecx,[edx].ios_i

    .endif

    add ecx,[edx].ios_bp
    inc [edx].ios_i
    mov [ecx],al
    mov eax,1
    ret

ioputc endp


oseek proc offs, from

    mov eax,offs
    xor edx,edx

    ioseek(&STDI, edx::eax, from)

    .ifnz

        .if !( STDI.ios_flag & IO_MEMBUF )

            push edx
            push eax

            ioread(&STDI)

            pop eax
            pop edx

        .endif
    .endif
    ret

oseek endp


oread proc

    mov ecx,STDI.ios_c
    sub ecx,STDI.ios_i

    .if ecx < eax

        push eax

        ioread( &STDI )

        pop eax

        .return 0 .ifz

        mov ecx,STDI.ios_c
        sub ecx,STDI.ios_i

        .return 0 .if ecx < eax
    .endif

    mov eax,STDI.ios_bp
    add eax,STDI.ios_i
    ret

oread endp


oreadb proc uses ecx edx b:LPSTR, z

    mov eax,z

    oread()

    .ifnz

        memcpy(b, eax, z)
        mov ecx,z

    .else

        xor ecx,ecx
        mov edx,b

        .while ecx < z

            ogetc()
            .break .ifz

            mov [edx],al

            inc edx
            inc ecx
        .endw
    .endif

    mov eax,ecx
    ret

oreadb endp


oputc proc uses ecx

    mov ecx,STDO.ios_i
    .if ecx == STDO.ios_size

        push edx
        push eax

        ioflush(&STDO)

        pop  eax
        pop  edx

        .return 0 .ifz

        mov ecx,STDO.ios_i

    .endif

    add ecx,STDO.ios_bp
    inc STDO.ios_i
    mov [ecx],al
    mov eax,1
    ret

oputc endp


oungetc proc

    .while 1

        mov eax,STDI.ios_i

        .if eax

            dec STDI.ios_i
            add eax,STDI.ios_bp
            movzx eax,byte ptr [eax-1]

            .return

        .endif

        .if STDI.ios_flag & IO_MEMBUF

            .return -1
        .endif

        .if _lseeki64(STDI.ios_file, 0, SEEK_CUR) == -1

            .return .if edx == -1
        .endif

        mov ecx,STDI.ios_c  ; last read size to CX

        .if ecx > eax
            ;
            ; stream not align if above
            ;
            or  STDI.ios_flag,IO_ERROR

            .return -1

        .endif

        .return -1 .ifz ; EOF == top of file

        .if eax == STDI.ios_size && dword ptr STDI.ios_offset == 0

            .return -1
        .endif

        sub eax,ecx     ; adjust offset to start
        mov ecx,STDI.ios_size
        .if ecx >= eax

            mov ecx,eax
            xor eax,eax
        .else
            sub eax,ecx
        .endif

        push ecx
        oseek(eax, SEEK_SET)
        pop eax
        .return -1 .ifz

        .if eax > STDI.ios_c

            or STDI.ios_flag,IO_ERROR
            .return -1
        .endif

        mov STDI.ios_c,eax
        mov STDI.ios_i,eax
    .endw
    ret

oungetc endp


oprintf proc c format:LPSTR, argptr:VARARG

    mov ecx,ftobufin(format, &argptr)

    .while 1

        movzx eax,byte ptr [edx]
        add edx,1

        .break .if !eax

        .if eax == 10

            mov eax,STDO.ios_file
            .if _osfile[eax] & FH_TEXT

                mov eax,13
                .break .if !oputc()

                inc ecx
            .endif
            mov eax,10
        .endif

        .break .if !oputc()

    .endw

    mov eax,ecx
    ret

oprintf endp


osopen proc file:LPSTR, attrib, mode, action

    mov ecx,mode
    xor eax,eax

    .if ecx != M_RDONLY

        mov byte ptr _diskflag,1
    .endif

    .if ecx == M_RDONLY

        mov eax,FILE_SHARE_READ
    .endif

    _osopenA(file, ecx, eax, 0, action, attrib)
    ret

osopen endp


openfile proc fname:LPSTR, mode, action

    .if osopen(fname, _A_NORMAL, mode, action) == -1

        eropen(fname)
    .endif
    ret

openfile endp


ogetouth proc filename:LPSTR, mode

    .return .if osopen(filename, _A_NORMAL, mode, A_CREATE) != -1

    .return eropen(filename) .if errno != EEXIST

    mov eax,CONFIRM_DELETE
    .if confirmflag & CFDELETEALL

        confirm_delete(filename, 0)
    .endif

    .switch eax

    .case CONFIRM_JUMP

        .return 0

    .case CONFIRM_DELETEALL

        and confirmflag,not CFDELETEALL

    .case CONFIRM_DELETE

        setfattr(filename, 0)
        .return openfile(filename, mode, A_TRUNC)

    .endsw

    mov eax,-1
    ret

ogetouth endp


    end
