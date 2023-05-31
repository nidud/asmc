; _LOCTOTIME_T.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include winbase.inc

    .code

_loctotime_t proc uses rsi rdi rbx year:int_t, month:int_t, day:int_t, hour:int_t, minute:int_t, second:int_t
ifdef __UNIX__
    int 3
else
  local tb:tm

    ldr ecx,year
    ldr edx,month

    or  eax,-1
    lea ebx,[rcx-1900]

    .repeat

        .break .if ( ebx < _BASE_YEAR || ebx > _MAX_YEAR )

        mov eax,ebx

        lea rcx,_days
        mov ecx,[rcx+rdx*4-4]
        add ecx,day
        .if ( !( eax & 3 ) && edx > 2 )
            inc ecx
        .endif

        mov esi,ecx
        mov ecx,eax
        sub eax,_BASE_YEAR
        mov edx,365
        mul edx
        dec ecx
        shr ecx,2
        lea rax,[rax+rcx-_LEAP_YEAR_ADJUST]
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
        .if ( _daylight )
            .ifd ( _isindst( &tb ) )
                sub edi,3600
            .endif
        .endif
        mov eax,edi
    .until 1
endif
    ret

_loctotime_t endp

    end
