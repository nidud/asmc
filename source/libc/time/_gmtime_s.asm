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
    .ifs ( eax < _MIN_LOCAL_TIME )
endif
        .return( EINVAL )
    .endif
    mov rsi,rax
    xor edx,edx

    ; Determine the years since 1900. Start by ignoring leap years.

    mov ecx,_YEAR_SEC
    div rcx
    lea edi,[rax+70]
    mul rcx
    sub rsi,rax

    ; Correct for elapsed leap years

    imul rax,_ELAPSED_LEAP_YEARS(edi),_DAY_SEC
    sub rsi,rax
    _IS_LEAP_YEAR(edi)
    xchg eax,edi
    .ifs ( rsi < 0 )
        add rsi,_YEAR_SEC
        dec eax
        .if ( edi )
            add rsi,_DAY_SEC
        .endif
    .endif
    mov [rbx].tm_year,eax
    mov rax,rsi
    xor edx,edx
    mov ecx,_DAY_SEC
    div rcx
    mov [rbx].tm_yday,eax
    mul rcx
    sub rsi,rax
    lea rcx,_lpdays
    .if ( !edi )
        lea rcx,_days
    .endif
    .for ( eax = [rbx].tm_yday, edx = 0 : [rcx+rdx*4+4] < eax : edx++ )
    .endf
    mov [rbx].tm_mon,edx
    sub eax,[rcx+rdx*4]
    mov [rbx].tm_mday,eax

    ; Determine days since Sunday (0 - 6)

    mov rcx,timp
    mov rax,[rcx]
    mov ecx,_DAY_SEC
    xor edx,edx
    div rcx
    xor edx,edx
    add rax,_BASE_DOW
    mov ecx,7
    div rcx
    mov [rbx].tm_wday,edx

    ; Determine hours since midnight (0 - 23), minutes after the hour
    ; (0 - 59), and seconds after the minute (0 - 59).

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
