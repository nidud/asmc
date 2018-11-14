; LOCALTIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include limits.inc

    .code

localtime proc uses esi edi ptime: LPTIME

  local ptm, ltime

    mov eax,ptime
    mov eax,[eax]

    .repeat

        .ifs eax < 0
            xor eax,eax
            .break
        .endif
        mov esi,eax

        _tzset()

        .if esi > 3 * _DAY_SEC && esi < LONG_MAX - 3 * _DAY_SEC

            mov eax,esi
            sub eax,_timezone
            mov ltime,eax
            gmtime(addr ltime)
            mov ptm,eax
            .if _daylight
                .if _isindst(ptm)
                    add ltime,3600
                    gmtime(addr ltime)
                    mov ptm,eax
                    mov [eax].tm.tm_isdst,1
                .endif
            .endif
        .else
            gmtime(ptime)
            mov ptm,eax
            mov esi,eax
            mov eax,[eax].tm.tm_sec
            sub eax,_timezone
            mov edi,eax
            xor edx,edx
            mov ecx,60
            idiv ecx
            .ifs edx < 0
                add edx,ecx
                sub edi,ecx
            .endif
            mov [esi].tm.tm_sec,edx
            mov eax,edi
            xor edx,edx
            idiv ecx
            add eax,[esi].tm.tm_min
            mov edi,eax
            xor edx,edx
            idiv ecx
            .ifs edx < 0
                add edx,ecx
                sub edi,ecx
            .endif
            mov [esi].tm.tm_min,edx
            mov eax,edi
            xor edx,edx
            idiv ecx
            add eax,[esi].tm.tm_hour
            mov edi,eax
            xor edx,edx
            mov ecx,24
            idiv ecx
            .ifs edx < 0
                add edx,ecx
                sub edi,ecx
            .endif
            mov [esi].tm.tm_hour,edx
            mov eax,edi
            xor edx,edx
            idiv ecx
            mov edi,eax
            .ifs eax > 0
                mov eax,[esi].tm.tm_wday
                add eax,edi
                mov ecx,7
                xor edx,edx
                idiv ecx
                mov [esi].tm.tm_wday,edx
                add [esi].tm.tm_mday,edi
                add [esi].tm.tm_yday,edi
            .else
                .ifl
                    mov eax,[esi].tm.tm_wday
                    add eax,edi
                    mov ecx,7
                    add eax,ecx
                    xor edx,edx
                    idiv ecx
                    mov [esi].tm.tm_wday,edx
                    add [esi].tm.tm_mday,edi
                    mov eax,[esi].tm.tm_mday
                    .ifs eax <= 0
                        add [esi].tm.tm_mday,32
                        mov [esi].tm.tm_yday,365
                        mov [esi].tm.tm_mon,11
                        dec [esi].tm.tm_year
                    .else
                        add [esi].tm.tm_yday,edi
                    .endif
                .endif
            .endif
        .endif
        mov eax,ptm
    .until 1
    ret

localtime endp

    END
