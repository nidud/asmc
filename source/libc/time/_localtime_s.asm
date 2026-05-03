; _LOCALTIME_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; errno_t _localtime64_s( struct tm *ptm, const __time64_t *ptime );
; errno_t _localtime32_s( struct tm *ptm, const __time32_t *ptime );
;

include time.inc
include limits.inc
include errno.inc

    .code

_localtime_s proc uses rbx rdi tp:ptr tm, ptime:ptr time_t

   .new ltime:time_t

    ldr rbx,tp
    ldr rdx,ptime

    .if ( !rdx || !rbx )
        .return( EINVAL )
    .endif

    mov al,-1
    mov rdi,rbx
    mov ecx,tm
    rep stosb

    mov rax,[rdx]
ifdef _WIN64
    mov rcx,_MAX__TIME64_T
    .ifs ( rax < 0 || rax > rcx )
else
    .ifs ( eax < 0 )
endif
        .return( EINVAL )
    .endif
    mov ltime,rax
    _tzset()
    mov rax,ltime
ifdef _WIN64
    .ifs ( rax > 3 * _DAY_SEC )
        movsxd rcx,_timezone
else
    .ifs ( eax > 3 * _DAY_SEC && eax < LONG_MAX - 3 * _DAY_SEC )
        mov ecx,_timezone
endif
        sub rax,rcx
        mov ltime,rax
        .ifd _gmtime_s(rbx, &ltime)
            .return
        .endif
        .if ( _daylight )
            .ifd _isindst(rbx)
ifdef _WIN64
                movsxd rax,_dstbias
else
                mov eax,_dstbias
endif
                sub ltime,rax
                .ifd _gmtime_s(rbx, &ltime)
                    .return
                .endif
                mov [rbx].tm.tm_isdst,1
            .endif
        .endif
        .return( 0 )
    .endif
    .ifd _gmtime_s(rbx, ptime)
        .return
    .endif
    .ifd _isindst(rbx)
        mov eax,[rbx].tm.tm_sec
        sub eax,_timezone
        sub eax,_dstbias
        mov [rbx].tm.tm_isdst,1
    .else
        mov eax,[rbx].tm.tm_sec
        sub eax,_timezone
    .endif
    mov edi,eax
    mov ecx,60
    cdq
    idiv ecx
    .ifs ( edx < 0 )
        add edx,ecx
        sub edi,ecx
    .endif
    mov [rbx].tm.tm_sec,edx
    mov eax,edi
    cdq
    idiv ecx
    add eax,[rbx].tm.tm_min
    mov edi,eax
    cdq
    idiv ecx
    .ifs ( edx < 0 )
        add edx,ecx
        sub edi,ecx
    .endif
    mov [rbx].tm.tm_min,edx
    mov eax,edi
    cdq
    idiv ecx
    add eax,[rbx].tm.tm_hour
    mov edi,eax
    mov ecx,24
    cdq
    idiv ecx
    .ifs ( edx < 0 )
        add edx,ecx
        sub edi,ecx
    .endif
    mov [rbx].tm.tm_hour,edx
    mov eax,edi
    cdq
    idiv ecx
    mov edi,eax
    mov ecx,7

    .ifs ( edi > 0 )
        mov  eax,[rbx].tm.tm_wday
        add  eax,edi
        cdq
        idiv ecx
        mov  [rbx].tm.tm_wday,edx
        add  [rbx].tm.tm_mday,edi
        add  [rbx].tm.tm_yday,edi
    .elseifs ( edi < 0 )
        mov  eax,[rbx].tm.tm_wday
        add  eax,edi
        add  eax,ecx
        cdq
        idiv ecx
        mov  [rbx].tm.tm_wday,edx
        mov  eax,[rbx].tm.tm_wday
        add  eax,edi
        .ifs ( eax <= 0 )
            add [rbx].tm.tm_mday,31
            add [rbx].tm.tm_yday,edi
            add [rbx].tm.tm_yday,365
            mov [rbx].tm.tm_mon,11
            dec [rbx].tm.tm_year
        .else
            add [rbx].tm.tm_yday,edi
        .endif
    .endif
    xor eax,eax
    ret
    endp

    end
