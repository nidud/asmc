; _LOCTOTIME_T.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; time_t _loctotime_t(int yr, int mo, int dy, int hr, int mn, int sc, int dstflag);
; __time32_t _loctotime32_t(int yr, int mo, int dy, int hr, int mn, int sc, int dstflag);
; __time64_t _loctotime64_t(int yr, int mo, int dy, int hr, int mn, int sc, int dstflag);
;
include time.inc
include errno.inc
ifndef __UNIX__
ifdef _WIN64
undef _loctotime64_t
ALIAS <_loctotime64_t>=<_loctotime_t>
else
undef _loctotime32_t
ALIAS <_loctotime32_t>=<_loctotime_t>
endif
endif

.code

_loctotime_t proc uses rsi rdi rbx yr:int_t, mo:int_t, dy:int_t, hr:int_t, mn:int_t, sc:int_t, dstflag:int_t

   .new tb:tm
   .new isleap:int_t

    ldr ecx,yr
    ldr edx,mo
    ldr eax,dy
    ldr ebx,hr
    mov edi,mn
    mov esi,sc

    sub ecx,1900
    .switch
    .case ecx < _BASE_YEAR
    .case ecx > _MAX_YEAR
    .case !edx
    .case edx > 12
    .case !eax
    .case ebx > 23
    .case edi > 59
    .case esi > 59
    .return( _set_errno(EINVAL) )
    .endsw
    mov tb.tm_year,ecx
    mov tb.tm_mon,edx
    mov tb.tm_yday,eax
    mov tb.tm_hour,ebx
    mov tb.tm_min,edi
    mov tb.tm_sec,esi
    mov isleap,_IS_LEAP_YEAR(ecx)
    lea rcx,_days
    mov edx,tb.tm_mon
    mov eax,[rcx+rdx*4]
    sub eax,[rcx+rdx*4-4]
    .if ( eax >= tb.tm_yday || ( isleap && edx == 2 && tb.tm_yday <= 29 ) )
        .return( _set_errno(EINVAL) )
    .endif

    ; Compute the number of elapsed days in the current year.

    mov eax,[rcx+rdx*4-4]
    add eax,tb.tm_yday
    .if ( isleap && edx > 2 )
        inc eax
    .endif
    mov tb.tm_yday,eax

    ; Compute the number of elapsed seconds since the Epoch. Note the
    ; computation of elapsed leap years would break down after 2100
    ; if such values were in range (fortunately, they aren't).

ifdef _WIN64
    _ELAPSED_LEAP_YEARS(tb.tm_year)
else
    mov  eax,tb.tm_year
    dec  eax
    shr  eax,2
    sub  eax,_LEAP_YEAR_ADJUST
endif
    mov  ecx,tb.tm_year
    sub  ecx,_BASE_YEAR
    imul rcx,rcx,365
    add  rcx,rax
    mov  eax,tb.tm_yday
    add  rcx,rax
    imul rcx,rcx,24
    add  rbx,rcx
    imul rbx,rbx,60 ; convert to minutes and add in mn
    add  rbx,rdi
    imul rbx,rbx,60 ; convert to seconds and add in sc
    add  rbx,rsi

    _tzset()
ifdef _WIN64
    movsxd rax,_timezone
    add rbx,rax
else
    add ebx,_timezone
endif

    ; Fill in enough fields of tb for _isindst(), then call it to determine DST.

    dec tb.tm_mon
    .if ( dstflag == 1 )
ifdef _WIN64
        movsxd rax,_dstbias
        add rbx,rax
else
        add ebx,_dstbias
endif
    .elseif ( dstflag == -1 && _daylight )
        .ifd _isindst(&tb)
ifdef _WIN64
            movsxd rax,_dstbias
            add rbx,rax
else
            add ebx,_dstbias
endif
        .endif
    .endif
    mov rax,rbx
    ret
    endp

    end
