include iost.inc

    .code

    assume edx:ptr S_IOST
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

    END
