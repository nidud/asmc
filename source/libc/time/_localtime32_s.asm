; _LOCALTIME32_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include limits.inc
include errno.inc

    .code

_localtime32_s proc uses rbx rdi tp:ptr tm, ptime:LPTIME

   .new ltime[2]:long_t

    ldr rcx,tp
    ldr rdx,ptime

    .if ( !rdx || !rcx || int_t ptr [rdx] < 0 )

        .return( EINVAL )
    .endif

    mov rbx,rcx
    mov eax,[rdx]
    mov ltime,eax

    mov al,-1
    mov rdi,rcx
    mov ecx,tm
    rep stosb

    _tzset()

    .if ( ltime > 3 * _DAY_SEC && ltime < LONG_MAX - 3 * _DAY_SEC )

        mov eax,ltime
        sub eax,_timezone
        mov ltime,eax

        .ifd ( _gmtime32_s( rbx, &ltime ) != 0 )

            .return
        .endif

        .if ( _isindst( rbx ) && _daylight )

            mov eax,_dstbias
            sub ltime,eax
            .ifd ( _gmtime32_s( rbx, &ltime ) != 0 )

                .return
            .endif
            mov [rbx].tm.tm_isdst,1
        .endif
        .return( 0 )
    .endif

    .ifd ( _gmtime32_s( rbx, ptime ) != 0 )

        .return
    .endif

    .ifd ( _isindst( rbx ) && _daylight )

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
    .return( 0 )

_localtime32_s endp

    end
