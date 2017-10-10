include iost.inc
include io.inc
include string.inc

    .code

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

    END
