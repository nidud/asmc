; _GMTIME_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; errno_t __cdecl _gmtime32_s(struct tm *ptm, const __time32_t *timp);
; errno_t __cdecl _gmtime64_s(struct tm *ptm, const __time64_t *timp);
;
include time.inc
include errno.inc

    .code

    assume rbx:ptr tm

_gmtime_s proc uses rsi rdi rbx ptm:ptr tm, timp:ptr time_t

   .new islpyr:int_t = 0 ; is-current-year-a-leap-year flag

    ldr rbx,ptm
    ldr rdx,timp

    .if ( !rdx || !rbx )
        .return( EINVAL )
    .endif

    mov al,-1
    mov rdi,rbx
    mov ecx,tm
    rep stosb
    mov rax,[rdx]
ifdef _WIN64
    mov rcx,_MAX__TIME64_T + _MAX_LOCAL_TIME
    .ifs ( rax < _MIN_LOCAL_TIME || rax > rcx )
else
    .ifs ( rax < _MIN_LOCAL_TIME )
endif
        .return( EINVAL )
    .endif
    mov rsi,rax
    xor edx,edx

ifdef _WIN64

    ; Determine the years since 1900. Start by ignoring leap years.

    mov ecx,_YEAR_SEC
    div ecx
    lea edi,[rax+70]
    mul rcx
    sub rsi,rax

    ; Correct for elapsed leap years

    imul rax,_ELAPSED_LEAP_YEARS(edi),_DAY_SEC
    sub rsi,rax
    _IS_LEAP_YEAR(edi)
    .ifs ( rsi < 0 )
        add rsi,_YEAR_SEC
        dec edi
        .if ( eax )
            add rsi,_DAY_SEC
            inc islpyr
        .endif
    .elseif ( eax )
        inc islpyr
    .endif

else

    mov ecx,_FOUR_YEAR_SEC
    div ecx
    lea edi,[rax*4+70]
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
                inc islpyr
            .endif
        .endif
    .endif

endif

    mov [rbx].tm_year,edi
    mov rax,rsi
    xor edx,edx
    mov ecx,_DAY_SEC
    div rcx
    mov [rbx].tm_yday,eax
    mul rcx
    sub rsi,rax
    .if ( islpyr )
        lea rcx,_lpdays
    .else
        lea rcx,_days
    .endif
    .for ( edx = 1 : [rcx+rdx*4] < [rbx].tm_yday : edx++ )
    .endf
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
    xor eax,eax
    ret
    endp

    end
