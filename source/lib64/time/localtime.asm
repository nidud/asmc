include time.inc
include limits.inc

    .code

localtime proc uses rsi rdi ptime: LPTIME

  local ptm:qword, ltime

    .repeat

        mov eax,[rcx]
        .ifs eax < 0
            xor eax,eax
            .break
        .endif
        mov esi,eax
        _tzset()

        .repeat

            .if esi > 3 * _DAY_SEC && esi < LONG_MAX - 3 * _DAY_SEC

                mov eax,esi
                sub eax,_timezone
                mov ltime,eax
                gmtime( &ltime )
                mov ptm,rax
                .break .if !_daylight
                .break .if !_isindst( ptm )
                add ltime,3600
                gmtime( addr ltime )
                mov ptm,rax
                mov [rax].tm.tm_isdst,1
                .break
            .endif

            gmtime( ptime )
            mov ptm,rax
            mov rsi,rax
            mov eax,[rax].tm.tm_sec
            sub eax,_timezone
            mov edi,eax
            xor edx,edx
            mov ecx,60
            idiv ecx
            .ifs edx < 0
                add edx,ecx
                sub edi,ecx
            .endif

            mov  [rsi].tm.tm_sec,edx
            mov  eax,edi
            xor  edx,edx
            idiv ecx
            add  eax,[rsi].tm.tm_min
            mov  edi,eax
            xor  edx,edx
            idiv ecx
            .ifs edx < 0
                add edx,ecx
                sub edi,ecx
            .endif

            mov  [rsi].tm.tm_min,edx
            mov  eax,edi
            xor  edx,edx
            idiv ecx
            add  eax,[rsi].tm.tm_hour
            mov  edi,eax
            xor  edx,edx
            mov  ecx,24
            idiv ecx
            .ifs edx < 0
                add edx,ecx
                sub edi,ecx
            .endif

            mov  [rsi].tm.tm_hour,edx
            mov  eax,edi
            xor  edx,edx
            idiv ecx
            mov  edi,eax
            .ifs eax > 0
                mov  eax,[rsi].tm.tm_wday
                add  eax,edi
                mov  ecx,7
                xor  edx,edx
                idiv ecx
                mov  [rsi].tm.tm_wday,edx
                add  [rsi].tm.tm_mday,edi
                add  [rsi].tm.tm_yday,edi
                .break
            .endif
            .break .ifnl

            mov  eax,[rsi].tm.tm_wday
            add  eax,edi
            mov  ecx,7
            add  eax,ecx
            xor  edx,edx
            idiv ecx
            mov  [rsi].tm.tm_wday,edx
            add  [rsi].tm.tm_mday,edi
            mov  eax,[esi].tm.tm_mday
            .ifs eax <= 0
                add [rsi].tm.tm_mday,32
                mov [rsi].tm.tm_yday,365
                mov [rsi].tm.tm_mon,11
                dec [rsi].tm.tm_year
            .else
                add [rsi].tm.tm_yday,edi
            .endif
        .until 1
        mov rax,ptm
    .until 1
    ret
localtime endp

    end
