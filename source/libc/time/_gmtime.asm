; _GMTIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc

    .code

    assume rbx:ptr tm

_gmtime proc uses rsi rdi rbx timp:ptr time_t, tmp:ptr tm

   .new leap:int_t = 0

    ldr rcx,timp
    ldr rbx,tmp

    mov eax,[rcx]

    .ifs ( eax < 0 )

        .return( NULL )
    .endif

    mov esi,eax
    xor edx,edx
    mov ecx,_FOUR_YEAR_SEC
    div ecx
    lea rdi,[rax*4+70]
    mul ecx
    sub esi,eax

    .if ( esi >= _YEAR_SEC )
        inc edi
        sub esi,_YEAR_SEC
        .if ( esi >= _YEAR_SEC )
            inc edi
            sub esi,_YEAR_SEC
            .if ( esi >= _YEAR_SEC + _DAY_SEC )
                inc edi
                sub esi,_YEAR_SEC + _DAY_SEC
            .else
                inc leap
            .endif
        .endif
    .endif

    mov [rbx].tm_year,edi
    mov eax,esi
    xor edx,edx
    mov ecx,_DAY_SEC
    div ecx
    mov [rbx].tm_yday,eax
    mul ecx
    sub esi,eax
    mov edx,1

    .if ( leap )
        lea rcx,_lpdays
    .else
        lea rcx,_days
    .endif
    .while 1

        mov eax,[rcx+rdx*4]
        .break .if ( eax >= [rbx].tm_yday )
        inc edx
    .endw

    dec edx
    mov [rbx].tm_mon,edx
    mov eax,[rbx].tm_yday
    sub eax,[rcx+rdx*4]
    mov [rbx].tm_mday,eax
    mov rax,timp
    mov eax,[rax]
    mov ecx,_DAY_SEC
    xor edx,edx
    div ecx
    xor edx,edx
    add eax,_BASE_DOW
    mov ecx,7
    div ecx
    mov [rbx].tm_wday,edx
    mov eax,esi
    xor edx,edx
    mov ecx,3600
    div ecx
    mov [rbx].tm_hour,eax
    mul ecx
    sub esi,eax
    mov eax,esi
    xor edx,edx
    mov ecx,60
    div ecx
    mov [rbx].tm_min,eax
    mul ecx
    sub esi,eax
    mov [rbx].tm_sec,esi
    mov [rbx].tm_isdst,0
    mov rax,rbx
    ret

_gmtime endp

    end
