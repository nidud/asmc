include time.inc

    .data
    tb tm <>

    .code

gmtime proc uses esi edi ebx timp: LPTIME

    xor ebx,ebx
    mov eax,timp
    mov eax,[eax]

    .repeat

        .ifs eax < ebx

            xor eax,eax
            .break
        .endif

        mov esi,eax
        xor edx,edx
        mov ecx,_FOUR_YEAR_SEC
        div ecx
        lea edi,[eax*4+70]
        mul ecx
        sub esi,eax
        .if esi >= _YEAR_SEC
            inc edi
            sub esi,_YEAR_SEC
            .if esi >= _YEAR_SEC
                inc edi
                sub esi,_YEAR_SEC
                .if esi >= _YEAR_SEC + _DAY_SEC
                    inc edi
                    sub esi,_YEAR_SEC + _DAY_SEC
                .else

                    inc ebx
                .endif
            .endif
        .endif

        mov tb.tm_year,edi
        mov eax,esi
        xor edx,edx
        mov ecx,_DAY_SEC
        div ecx
        mov tb.tm_yday,eax
        mul ecx
        sub esi,eax
        mov edx,1
        test ebx,ebx
        lea ebx,_lpdays
        .ifz
            lea ebx,_days
        .endif

        .while 1

            mov eax,[ebx+edx*4]
            .break .if eax >= tb.tm_yday
            inc edx
        .endw

        dec edx
        mov tb.tm_mon,edx
        mov eax,tb.tm_yday
        sub eax,[ebx+edx*4]
        mov tb.tm_mday,eax
        mov eax,timp
        mov eax,[eax]
        mov ecx,_DAY_SEC
        xor edx,edx
        div ecx
        xor edx,edx
        add eax,_BASE_DOW
        mov ecx,7
        div ecx
        mov tb.tm_wday,edx
        mov eax,esi
        xor edx,edx
        mov ecx,3600
        div ecx
        mov tb.tm_hour,eax
        mul ecx
        sub esi,eax
        mov eax,esi
        xor edx,edx
        mov ecx,60
        div ecx
        mov tb.tm_min,eax
        mul ecx
        sub esi,eax
        mov tb.tm_sec,esi
        xor eax,eax
        mov tb.tm_isdst,eax
        or  eax,offset tb
    .until 1
    ret

gmtime endp

    END
