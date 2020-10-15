; _LOCTOTIME_T.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc

    .code

_loctotime_t proc uses esi edi ebx year:SINT, month:SINT, day:SINT, hour:SINT, minute:SINT, second:SINT

  local tb:tm

    mov eax,year
    sub eax,1900
    mov ebx,eax

    .return 0 .if eax < _BASE_YEAR || eax > _MAX_YEAR

    mov edx,month
    mov ecx,_days[edx*4-4]
    add ecx,day
    .if !(eax & 3) && edx > 2
        inc ecx
    .endif

    mov esi,ecx
    mov ecx,eax
    sub eax,_BASE_YEAR
    mov edx,365
    mul edx
    dec ecx
    shr ecx,2
    lea eax,[eax+ecx-_LEAP_YEAR_ADJUST]
    add eax,esi
    mov ecx,24
    mul ecx
    add eax,hour
    mov ecx,60
    mul ecx
    add eax,minute
    mul ecx
    add eax,second
    mov edi,eax

    _tzset()
    add edi,_timezone

    mov ecx,month
    dec ecx
    mov edx,hour
    mov tb.tm_yday,esi
    mov tb.tm_year,ebx
    mov tb.tm_mon,ecx
    mov tb.tm_hour,edx
    .if _daylight
        .if _isindst(&tb)
            sub edi,3600
        .endif
    .endif
    mov eax,edi
    ret

_loctotime_t endp

    END
