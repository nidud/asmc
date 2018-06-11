include time.inc

    .data
    tb tm <>

    .code

gmtime proc uses rsi rdi rbx timp: LPTIME

    xor ebx,ebx
    mov eax,[rcx]
    .ifs eax >= ebx
        mov esi,eax
        xor edx,edx
        mov ecx,_FOUR_YEAR_SEC
        div ecx
        lea rdi,[rax*4+70]
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
        .if ebx
            lea rbx,_lpdays
        .else
            lea rbx,_days
        .endif
        .while 1
            mov eax,[rbx+rdx*4]
            .break .if eax >= tb.tm_yday
            inc edx
        .endw
        dec edx
        mov tb.tm_mon,edx
        mov eax,tb.tm_yday
        sub eax,[rbx+rdx*4]
        mov tb.tm_mday,eax
        mov rax,timp
        mov eax,[rax]
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
        lea eax,tb
    .else
        xor eax,eax
    .endif
    ret
gmtime endp

    end
