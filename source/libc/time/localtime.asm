; LOCALTIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include limits.inc

    .code

localtime proc uses rbx rdi ptime: LPTIME

  local ptm:ptr tm, ltime:time_t

    ldr rcx,ptime
    mov ebx,[rcx]

    .return 0 .ifs ( ebx < 0 )

    _tzset()

    .repeat

        .if ( ebx > 3 * _DAY_SEC && ebx < LONG_MAX - 3 * _DAY_SEC )

            mov eax,ebx
            sub eax,_timezone
            mov ltime,rax
            mov ptm,gmtime( &ltime )

            .break .if !_daylight
            .break .if !_isindst( ptm )

            add ltime,3600
            mov ptm,gmtime( &ltime )
            mov [rax].tm.tm_isdst,1
            .break

        .endif

        mov ptm,gmtime( ptime )
        mov rbx,rax
        mov eax,[rax].tm.tm_sec
        sub eax,_timezone
        mov edi,eax
        xor edx,edx
        mov ecx,60
        idiv ecx

        .ifs ( edx < 0 )

            add edx,ecx
            sub edi,ecx
        .endif

        mov  [rbx].tm.tm_sec,edx
        mov  eax,edi
        xor  edx,edx
        idiv ecx
        add  eax,[rbx].tm.tm_min
        mov  edi,eax
        xor  edx,edx
        idiv ecx

        .ifs ( edx < 0 )

            add edx,ecx
            sub edi,ecx
        .endif

        mov  [rbx].tm.tm_min,edx
        mov  eax,edi
        xor  edx,edx
        idiv ecx
        add  eax,[rbx].tm.tm_hour
        mov  edi,eax
        xor  edx,edx
        mov  ecx,24
        idiv ecx

        .ifs ( edx < 0 )

            add edx,ecx
            sub edi,ecx
        .endif

        mov  [rbx].tm.tm_hour,edx
        mov  eax,edi
        xor  edx,edx
        idiv ecx
        mov  edi,eax

        .ifs ( eax > 0 )

            mov  eax,[rbx].tm.tm_wday
            add  eax,edi
            mov  ecx,7
            xor  edx,edx
            idiv ecx
            mov  [rbx].tm.tm_wday,edx
            add  [rbx].tm.tm_mday,edi
            add  [rbx].tm.tm_yday,edi
           .break
        .endif
        .break .ifnl

        mov  eax,[rbx].tm.tm_wday
        add  eax,edi
        mov  ecx,7
        add  eax,ecx
        xor  edx,edx
        idiv ecx
        mov  [rbx].tm.tm_wday,edx
        add  [rbx].tm.tm_mday,edi

        mov eax,[rbx].tm.tm_mday
        .ifs ( eax <= 0 )

            add [rbx].tm.tm_mday,32
            mov [rbx].tm.tm_yday,365
            mov [rbx].tm.tm_mon,11
            dec [rbx].tm.tm_year
        .else
            add [rbx].tm.tm_yday,edi
        .endif
    .until 1
    .return( ptm )

localtime endp

    end
