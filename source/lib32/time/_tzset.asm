include time.inc
include winbase.inc

    .code

_tzset proc uses esi

  local tz:TIME_ZONE_INFORMATION

    .if GetTimeZoneInformation(&tz) != -1

        mov ecx,60
        mov eax,tz.Bias
        mul ecx
        mov esi,eax
        .if tz.StandardDate.wMonth
            mov eax,tz.StandardBias
            mul ecx
            add esi,eax
        .endif
        mov _timezone,esi
        xor eax,eax
        .if tz.DaylightDate.wMonth != ax && tz.DaylightBias != eax

            inc eax
        .endif

        mov _daylight,eax
        xor eax,eax
        mov ecx,_tzname
        mov [ecx],al
        mov ecx,_tzname[4]
        mov [ecx],al
    .endif
    ret

_tzset endp

_isindst proc uses esi edi ebx tb:ptr tm

    mov esi,tb
    xor eax,eax
    mov ecx,[esi].tm.tm_mon
    mov edx,[esi].tm.tm_year

    .repeat

        .break .if edx < 67
        .break .if ecx < 3
        .break .if ecx > 9
        inc eax
        .break .if ecx > 3 && ecx < 9
        mov edi,edx
        mov ebx,_days[ecx*4+4]
        .if edx > 86 && ecx == 3
            mov ebx,_days[ecx*4]
            add ebx,7
        .endif

        .if !(edx & 3)
            inc ebx
        .endif

        lea eax,[ebx+365]
        lea ecx,[edx-70]
        mul ecx
        lea eax,[eax+edi-1]
        shr eax,2
        sub eax,_LEAP_YEAR_ADJUST + _BASE_DOW
        xor edx,edx
        mov ecx,7
        idiv ecx
        mov eax,1
        .if [esi].tm.tm_mon == 3

            .break .if [esi].tm.tm_yday > edx
            .ifz
                .break .if [esi].tm.tm_hour >= 2
            .endif
            dec eax
            .break
        .endif

        .break .if [esi].tm.tm_yday < edx
        .ifz
            .break .if [esi].tm.tm_hour < 1
        .endif
        dec eax
    .until 1
    ret

_isindst endp


    END
