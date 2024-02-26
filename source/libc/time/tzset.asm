; _TZSET.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include winbase.inc

    .code

_tzset proc uses rsi
ifdef __UNIX__
    int 3
else
  local tz:TIME_ZONE_INFORMATION

    .ifd ( GetTimeZoneInformation( &tz ) != -1 )

        mov ecx,60
        mov eax,tz.Bias
        mul ecx
        mov esi,eax

        .if ( tz.StandardDate.wMonth )

            mov eax,tz.StandardBias
            mul ecx
            add esi,eax
        .endif
        mov _timezone,esi

        xor eax,eax
        .if ( tz.DaylightDate.wMonth != ax && tz.DaylightBias != eax )
            inc eax
        .endif
        mov _daylight,eax

        xor eax,eax
        lea rdx,_tzname
        mov rcx,[rdx]
        mov [rcx],al
        mov rcx,[rdx+size_t]
        mov [rcx],al
    .endif
endif
    ret

_tzset endp


_isindst proc uses rsi rdi rbx tb:ptr tm

    ldr rsi,tb
    xor eax,eax
    mov ecx,[rsi].tm.tm_mon
    mov edx,[rsi].tm.tm_year

    .repeat

        .break .if ( edx < 67 )
        .break .if ( ecx < 3 )
        .break .if ( ecx > 9 )

        inc eax
        .break .if ( ecx > 3 && ecx < 9 )

        lea rax,_days
        mov edi,edx
        mov ebx,[rax+rcx*4+4]

        .if ( edx > 86 && ecx == 3 )
            mov ebx,[rax+rcx*4]
            add ebx,7
        .endif
        .if !(edx & 3)
            inc ebx
        .endif

        lea  rax,[rbx+365]
        lea  rcx,[rdx-70]
        mul  ecx
        lea  rax,[rax+rdi-1]
        shr  eax,2
        sub  eax,_LEAP_YEAR_ADJUST + _BASE_DOW
        xor  edx,edx
        mov  ecx,7
        idiv ecx
        mov  eax,1

        .if ( [rsi].tm.tm_mon == 3 )

            .break .if ( [rsi].tm.tm_yday > edx )
            .ifnz
                dec eax
                .break
            .endif
            .break .if ( [rsi].tm.tm_hour >= 2 )
            dec eax
            .break
        .endif
        .break .if ( [rsi].tm.tm_yday < edx )
        .ifnz
            dec eax
        .elseif ( [rsi].tm.tm_hour >= 1 )
            dec eax
        .endif
    .until 1
    ret

_isindst endp

    end
