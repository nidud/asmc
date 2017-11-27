include tinfo.inc
include io.inc
include direct.inc
include string.inc
include stdio.inc
include errno.inc
include dzlib.inc

    .data
    new_id  dd 0

    .code

    assume esi:ptr S_TINFO
    assume edi:ptr S_TINFO

topen proc uses esi edi file:LPSTR, tflag:UINT

    .if tiopen(tinfo, titabsize, tiflags)

        mov esi,eax
        or  [esi].ti_flag,_T_FILE
        mov edi,[esi].ti_prev
        mov tinfo,eax
        mov eax,tflag
        .if eax

            and [esi].ti_flag,NOT _T_TECFGMASK
            or  [esi].ti_flag,eax
        .endif

        mov eax,file
        .if eax

            .if byte ptr [strcpy([esi].ti_file, eax) + 1] != ':'

                GetFullPathName(eax, _MAX_PATH * 2, eax, 0)
            .endif

            .if tireadstyle(esi)

                tiread(esi)
            .else
                ermsg (0, addr CP_ENOMEM)

                ticlose(esi)
                xor esi,esi
            .endif
        .else
            and [esi].ti_flag,NOT _T_UNREAD
            inc [esi].S_TINFO.ti_lcnt   ; set line count to 1
            .repeat
                inc new_id
                sprintf([esi].ti_file, "New (%d)", new_id)
                filexist([esi].ti_file)
            .until  eax != 1

            .if edi

                memcpy([esi].ti_style, [edi].ti_style, STYLESIZE)
                mov eax,[edi].ti_stat
                mov [esi].ti_stat,eax
            .else
                tireadstyle(esi)
            .endif
        .endif
        mov eax,esi
    .endif
    test eax,eax
    ret

topen endp

tclose proc

    .if tistate(tinfo)
        .if ecx & _T_MODIFIED
            mov edx,tinfo
            .if SaveChanges([edx].S_TINFO.ti_file)

                tiflush(tinfo)
            .endif
        .endif
        ticlose(tinfo)
        mov tinfo,eax
    .else
        mov new_id,eax
    .endif
    ret

tclose endp

tcloseall proc

    tclose()
    test eax,eax
    jnz tcloseall
    ret

tcloseall endp

    END
