; _LOCTOTIME_T.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc

    .code

_loctotime_t proc uses rbx year:int_t, month:int_t, day:int_t, hour:int_t, minute:int_t, second:int_t

  local tb:tm

    ldr ecx,year
    ldr edx,month

    lea eax,[rcx-1900]
    .if ( eax < _BASE_YEAR || eax > _MAX_YEAR )

        .return( -1 )
    .endif
    mov tb.tm_year,eax
    lea rcx,_days
    mov ecx,[rcx+rdx*4-4]
    add ecx,day
    .if ( !( eax & 3 ) && edx > 2 )
        inc ecx
    .endif
    mov tb.tm_yday,ecx
    mov ecx,eax
    sub eax,_BASE_YEAR
    mov edx,365
    mul edx
    dec ecx
    shr ecx,2
    lea rbx,[rax+rcx-_LEAP_YEAR_ADJUST]
    add ebx,tb.tm_yday
    mov ecx,24
    mul ecx
    add ebx,hour
    mov ecx,60
    mul ecx
    add ebx,minute
    mul ecx
    add ebx,second
    _tzset()
    add ebx,_timezone
    mov ecx,month
    dec ecx
    mov edx,hour
    mov tb.tm_mon,ecx
    mov tb.tm_hour,edx
    .if ( _daylight )
        .ifd ( _isindst( &tb ) )
            sub ebx,3600
        .endif
    .endif
    mov eax,ebx
    ret

_loctotime_t endp

    end
