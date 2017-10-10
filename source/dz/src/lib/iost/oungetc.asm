include iost.inc
include io.inc

    .code

oungetc proc

    .while 1

        mov eax,STDI.ios_i
        .if eax
            dec STDI.ios_i
            add eax,STDI.ios_bp
            movzx eax,byte ptr [eax-1]
            .break
        .endif


        .if STDI.ios_flag & IO_MEMBUF

            dec eax
            .break
        .endif

        .if _lseeki64(STDI.ios_file, 0, SEEK_CUR) == -1

            .break .if edx == -1
        .endif

        mov ecx,STDI.ios_c  ; last read size to CX
        .if ecx > eax
            ;
            ; stream not align if above
            ;
            or  STDI.ios_flag,IO_ERROR
            or eax,-1
            .break
        .endif

        .ifz
            ;
            ; EOF == top of file
            ;
            or eax,-1
            .break
        .endif

        .if eax == STDI.ios_size && dword ptr STDI.ios_offset == 0

            or eax,-1
            .break
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

        .ifz

            or eax,-1
            .break
        .endif

        .if eax > STDI.ios_c

            or STDI.ios_flag,IO_ERROR
            or eax,-1
            .break
        .endif

        mov STDI.ios_c,eax
        mov STDI.ios_i,eax
    .endw
    ret

oungetc endp

    END
