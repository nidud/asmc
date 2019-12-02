include tinfo.inc

    .code

    assume edx:ptr S_TINFO

tioption proc uses esi edi ti:PTINFO

    mov edx,ti
    mov esi,titabsize
    mov edi,tiflags

    mov eax,[edx].ti_flag
    mov tiflags,eax

    mov eax,[edx].ti_tabz
    mov titabsize,eax

    toption()
    .repeat

        mov eax,titabsize
        mov ecx,tiflags
        mov tiflags,edi
        mov titabsize,esi

        mov edx,ti
        .break .if eax == [edx].ti_tabz && ecx == [edx].ti_flag

        mov esi,eax
        mov eax,[edx].ti_flag
        mov edi,eax
        and ecx,_T_TECFGMASK
        and eax,not _T_TECFGMASK
        or  eax,ecx
        mov [edx].ti_flag,eax

        mov eax,edi
        and eax,_T_USETABS
        and ecx,_T_USETABS

        .if eax != ecx || esi != [edx].ti_tabz

            .if edi & _T_MODIFIED

                .if SaveChanges([edx].ti_file)

                    tiflush(ti)
                .endif
            .endif
            mov edx,ti
            mov [edx].ti_tabz,esi
            tireload(edx)
        .endif
    .until 1
    ret

tioption endp

    END
