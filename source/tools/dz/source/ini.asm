; INI.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include string.inc
include malloc.inc
include ini.inc
include iost.inc
include io.inc
include iost.inc
include dzlib.inc
include ltype.inc

    .code


INIAlloc proc

    .if malloc(S_INI)

        mov ecx,0
        mov [eax].S_INI.flags,ecx
        mov [eax].S_INI.entry,ecx
        mov [eax].S_INI.value,ecx
        mov [eax].S_INI.next,ecx
    .endif
    ret

INIAlloc endp


INIRead proc uses esi edi ebx ini:LPINI, file:LPSTR

  local i_fh, i_bp, i_i, i_c, o_bp, o_i, o_c

    .if osopen(file, _A_NORMAL, M_RDONLY, A_OPEN) != -1

        mov i_fh,eax
        mov i_bp,alloca(_PAGESIZE_*2)
        add eax,_PAGESIZE_
        mov o_bp,eax
        xor eax,eax
        mov i_i,eax
        mov i_c,eax
        mov o_i,eax
        mov o_c,eax
        .if eax == ini

            mov ini,INIAlloc()
        .endif
        mov ebx,ini

        .while 1

            mov eax,i_i
            .if eax == i_c

                .break .if !osread(i_fh, i_bp, _PAGESIZE_)

                mov i_c,eax
                xor eax,eax
                mov i_i,eax
            .endif

            inc i_i
            add eax,i_bp
            movzx eax,byte ptr [eax]

            mov edi,o_bp
            mov edx,o_i
            inc o_i
            mov [edi+edx],ax

            .if eax == 10 || edx == _PAGESIZE_ - 2

                mov o_i,0
                mov al,[edi]

                .switch al

                  .case 10
                  .case 13
                    .endc
                  .case '['
                    inc edi
                    .if strchr(edi, ']')

                        mov byte ptr [eax],0
                        .break .if !INIAddSection(ini, edi)
                        mov ebx,eax
                    .endif
                    .endc
                  .default
                    INIAddEntry(ebx, edi)
                .endsw
            .endif
        .endw

        _close(i_fh)
        mov eax,ini
    .else

        xor eax,eax
    .endif
    ret

INIRead endp


    assume esi:ptr S_INI
    assume edi:ptr S_INI

INIWrite proc uses esi edi ebx ini:LPINI, file:LPSTR

    .if osopen(file, _A_NORMAL, M_WRONLY, A_CREATETRUNC) != -1

        mov STDO.ios_file,eax
        or  _osfile[eax],FH_TEXT

        .if ioinit(&STDO, OO_MEM64K)

            mov esi,ini
            .while esi

                .if [esi].flags == INI_SECTION

                    oprintf("\n[%s]\n", [esi].entry)
                .endif

                mov edi,[esi].value
                .while edi

                    .if [edi].flags == INI_ENTRY

                        oprintf("%s=%s\n", [edi].entry, [edi].value)
                    .elseif [edi].flags == INI_COMMENT

                        oprintf("%s\n", [edi].entry)
                    .else
                        oprintf( ";%s\n", [edi].entry)
                    .endif

                    mov edi,[edi].next
                .endw

                mov esi,[esi].next
            .endw

            ioflush(&STDO)
            ioclose(&STDO)
            mov eax,1
        .else

            _close(STDO.ios_file)
            xor eax,eax
        .endif
    .else

        xor eax,eax
    .endif
    ret

INIWrite endp


INIAddEntry proc __cdecl uses esi edi ebx cf:LPINI, string:LPSTR

    xor edi,edi
    mov esi,string

    movzx eax,byte ptr [esi]
    .while _ltype[eax+1] & _SPACE

    add esi,1
    mov al,[esi]
    .endw

    .repeat
    .if al == ';'

        .break .if !INIAlloc()

        mov edi,eax
        strtrim(esi)
        mov [edi].S_INI.flags,INI_COMMENT
        mov [edi].S_INI.entry,_strdup(esi)
        mov eax,edi

    .elseif strchr(esi, '=')

        mov byte ptr [eax],0
        lea edi,[eax+1]

        movzx eax,byte ptr [edi]
        .while _ltype[eax+1] & _SPACE

        add edi,1
        mov al,[edi]
        .endw

        .break .if !strtrim(esi)
        mov ebx,eax
        .break .if !strtrim(edi)
        lea ebx,[ebx+eax+2]

        .if INIGetEntry(cf, esi)

        mov eax,[ecx].S_INI.next
        .if !edx
            mov edx,cf
            mov [edx].S_INI.value,eax
        .else
            mov [edx].S_INI.next,eax
        .endif
        push ecx
        free([ecx].S_INI.entry)
        pop eax
        free(eax)
        .endif
        .break .if !INIAlloc()

        xchg ebx,eax
        .break .if !malloc(eax)

        mov [ebx].S_INI.entry,eax
        strcat(strcat(strcpy(eax, esi), "="), edi)
        strchr(eax, '=')
        mov byte ptr [eax],0
        inc eax
        mov [ebx].S_INI.value,eax

        mov eax,ebx
        mov [eax].S_INI.flags,INI_ENTRY
    .endif

    mov edx,cf
    mov ecx,[edx].S_INI.value
    .if ecx
        .while [ecx].S_INI.next

        mov ecx,[ecx].S_INI.next
        .endw
        mov [ecx].S_INI.next,eax
    .else
        mov [edx].S_INI.value,eax
    .endif
    .until 1
    ret

INIAddEntry endp


INIAddEntryX proc c ini:LPINI, format:LPSTR, argptr:VARARG


    .if ftobufin(format, &argptr)

        INIAddEntry(ini, edx)
    .endif

    ret

INIAddEntryX endp


INIAddSection proc uses esi ini:LPINI, section:LPSTR

    .if !INIGetSection(ini, section)

        .if INIAlloc()

            mov esi,eax
            mov [esi].S_INI.flags,INI_SECTION
            mov [esi].S_INI.entry,_strdup(section)

            mov eax,ini
            .if eax
                .while [eax].S_INI.next

                    mov eax,[eax].S_INI.next
                .endw
                mov [eax].S_INI.next,esi
            .endif
            mov eax,esi
        .endif
    .endif
    ret

INIAddSection endp


INIAddSectionX proc c ini:LPINI, format:LPSTR, argptr:VARARG


    .if ftobufin(format, &argptr)

        INIAddSection(ini, edx)
    .endif

    ret

INIAddSectionX endp


INIDelEntries proc uses esi ini:LPINI

    mov eax,ini
    mov esi,[eax].S_INI.value
    mov [eax].S_INI.value,0

    .while esi

        .if [esi].S_INI.entry

            free([esi].S_INI.entry)
        .endif

        mov eax,esi
        mov esi,[esi].S_INI.next
        free(eax)
    .endw
    mov eax,ini
    ret

INIDelEntries endp


INIDelSection proc __cdecl ini:LPINI, section:LPSTR

    .if INIGetSection(ini, section)

        .if edx

            mov ecx,[eax].S_INI.next
            mov [edx].S_INI.next,ecx
        .endif

        .if free([INIDelEntries(eax)].S_INI.entry) == ini

            mov [eax].S_INI.flags,0
            mov [eax].S_INI.entry,0
        .else
            free(eax)
        .endif
        mov eax,ini
    .endif
    ret

INIDelSection endp


INIGetEntry proc __cdecl uses esi edi ini:LPINI, entry:LPSTR

    mov edx,ini
    xor edi,edi
    xor eax,eax

    .if edx && [edx].S_INI.flags & INI_SECTION

        mov eax,[edx].S_INI.value

        .while  eax

            .if [eax].S_INI.flags & INI_ENTRY

                mov esi,eax
                mov edx,[eax].S_INI.entry
                mov ecx,entry

                .while  1

                    mov al,[ecx]
                    mov ah,[edx]
                    .break .if !al

                    add ecx,1
                    add edx,1
                    or  eax,0x2020
                    .break .if al != ah
                .endw

                .if al == ah

                    mov edx,edi ; mother
                    mov ecx,esi ; entry
                    ;
                    ; return value
                    ;
                    mov eax,[esi].S_INI.value
                    .break
                .endif

                mov eax,esi
            .endif
            mov edi,eax
            mov eax,[eax].S_INI.next
        .endw
    .endif
    ret

INIGetEntry endp


INIGetEntryID proc __cdecl ini:LPINI, entry:UINT

    mov eax,entry ; 0..99
    .while  al > 9
        add ah,1
        sub al,10
    .endw
    .if ah
        xchg    al,ah
        or  ah,'0'
    .endif
    or  al,'0'
    mov entry,eax

    INIGetEntry(ini, &entry)
    ret

INIGetEntryID endp


INIGetSection proc uses esi edi ini:LPINI, section:LPSTR

    mov eax,ini
    xor edi,edi

    .while  eax

        .if [eax].S_INI.flags & INI_SECTION

            mov esi,eax
            .if !strcmp([esi].S_INI.entry, section)

                mov edx,edi
                mov eax,esi
                .break
            .endif
            mov eax,esi
        .endif
        mov edi,eax
        mov eax,[eax].S_INI.next
    .endw
    ret

INIGetSection endp


INIClose proc uses esi edi ebx ini:LPINI

    mov esi,ini

    .while esi

        .if [esi].entry

            free([esi].entry)
        .endif

        mov edi,[esi].value
        .while edi

            .if [edi].entry

                free([edi].entry)
            .endif

            mov eax,edi
            mov edi,[edi].next
            free(eax)
        .endw

        mov eax,esi
        mov esi,[esi].next
        free(eax)
    .endw
    ret

INIClose endp

    END
