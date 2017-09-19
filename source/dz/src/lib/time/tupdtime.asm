include time.inc
include consx.inc
include winnls.inc

    .data
    _sec    dd 61
    iso_s   db "dd.MM.yy",0

    .code

tupdtime proc uses esi edi ebx

local ts:SYSTEMTIME
local buf[64]:byte

    mov ebx,console
    xor eax,eax

    .if ebx & CON_UTIME or CON_UDATE

        mov buf,al
        mov ecx,SIZE SYSTEMTIME/4
        lea edi,ts
        rep stosd
        mov edi,ebx
        GetLocalTime(&ts)

        mov eax,edi
        and eax,CON_UTIME or CON_LTIME
        cmp eax,CON_UTIME or CON_LTIME
        movzx eax,ts.wSecond
        .ifnz
            movzx eax,ts.wMinute
        .endif

        .if eax != _sec

            mov _sec,eax
            mov esi,GetUserDefaultLCID()
            mov ebx,_scrcol
            inc ebx

            .if edi & CON_UTIME

                mov edx,TIME_NOSECONDS
                .if edi & CON_LTIME

                    xor edx,edx
                .endif
                .if GetTimeFormat(esi, edx, &ts, 0, &buf, 32)

                    sub ebx,eax
                    scputs(ebx, 0, 0, 0, &buf)
                .endif
            .endif

            .if edi & CON_UDATE

                lea edx,iso_s
                .if edi & CON_LDATE

                    xor edx,edx
                .endif
                .if GetDateFormat(esi, 0, &ts, edx, &buf, 32)

                    sub ebx,eax
                    scputs(ebx, 0, 0, 0, &buf)
                .endif
            .endif
        .endif
    .endif
    ret

tupdtime endp

    END
