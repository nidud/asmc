; MKTIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; time_t mktime(struct tm *tb);
; __time32_t _mktime32(struct tm *tb);
; __time64_t _mktime64(struct tm *tb);
; time_t _mkgmtime(struct tm *tb);
; __time32_t _mkgmtime32(struct tm *tb);
; __time64_t _mkgmtime64(struct tm *tb);
;

include time.inc
include errno.inc
ifndef __UNIX__
ifdef _WIN64
undef _mktime64
undef _mkgmtime64
ALIAS <_mktime64>=<mktime>
ALIAS <_mkgmtime64>=<_mkgmtime>
else
undef _mktime32
undef _mkgmtime32
ALIAS <_mktime32>=<mktime>
ALIAS <_mkgmtime32>=<_mkgmtime>
endif
endif

    .code

_make_time_t proc private uses rsi rdi rbx tp:ptr tm, ultflag:int_t

   .new tb:tm
   .new tmp:time_t

    ldr rbx,tp
    test rbx,rbx
    jnz test_range
err_mktime:
    .return( _set_errno(EINVAL) )

test_range:

    ; First, make sure tm_year is reasonably close to being in range.

    mov esi,[rbx].tm.tm_year
    .ifs ( ( esi < _BASE_YEAR - 1 ) || ( esi > _MAX_YEAR + 1 ) )
       jmp err_mktime
    .endif

    ; Adjust month value so it is in the range 0 - 11.  This is because
    ; we don't know how many days are in months 12, 13, 14, etc.

    mov edi,[rbx].tm.tm_mon
    .ifs ( edi < 0 || edi > 11 )

        mov eax,edi
        mov ecx,12
        cdq
        idiv ecx
        add esi,eax
        mov edi,edx
        .ifs ( edi < 0 )
            add edi,12
            dec esi
        .endif

        ; Make sure year count is still in range.

        .ifs ( ( esi < _BASE_YEAR - 1 ) || ( esi > _MAX_YEAR + 1 ) )
           jmp err_mktime
        .endif
    .endif
    mov [rbx].tm.tm_mon,edi

    ; Calculate days elapsed minus one, in the given year, to the given
    ; month. Check for leap year and adjust if necessary.

    _IS_LEAP_YEAR(esi)
    lea rdx,_days
    mov ecx,[rdx+rdi*4]
    .if ( eax && edi > 1 )
        inc ecx
    .endif
ifdef _WIN64
    movsxd rdi,ecx
else
    mov edi,ecx
endif

    ; Calculate elapsed days since base date (midnight, 1/1/70, UTC)
    ;
    ; 365 days for each elapsed year since 1970, plus one more day for
    ; each elapsed leap year. no danger of overflow because of the range
    ; check (above) on ESI.

    add rdi,_ELAPSED_LEAP_YEARS(esi)
    lea eax,[rsi-_BASE_YEAR]
    imul eax,eax,365

    ; elapsed days to current month (still no possible overflow)

    add rdi,rax

    ; elapsed days to current date. overflow is now possible.

    ; elapsed days to current date.

    mov eax,[rbx].tm.tm_mday
    lea rsi,[rdi+rax]

    ; HERE: rsi holds number of elapsed days

    ; Calculate elapsed hours since base date

    imul rcx,rsi,24
ifdef _WIN64
    mov eax,[rbx].tm.tm_hour
    lea rsi,[rax+rcx]
else
    jc err_mktime
    add ecx,[rbx].tm.tm_hour
    jc err_mktime
    mov esi,ecx
endif

    ; HERE: rsi holds number of elapsed hours

    imul rcx,rsi,60
ifdef _WIN64
    mov eax,[rbx].tm.tm_min
    lea rsi,[rax+rcx]
else
    jc err_mktime
    add ecx,[rbx].tm.tm_min
    jc err_mktime
    mov esi,ecx
endif

    ; HERE: rsi holds number of elapsed minutes

    ; Calculate elapsed seconds since base date

    imul rcx,rsi,60
ifdef _WIN64
    mov eax,[rbx].tm.tm_sec
    lea rsi,[rax+rcx]
else
    jc err_mktime
    add ecx,[rbx].tm.tm_sec
    jc err_mktime
    mov esi,ecx
endif

    ; HERE: rsi holds number of elapsed seconds

    mov tmp,rsi

    .if ( ultflag )

        ; Adjust for timezone. No need to check for overflow since
        ; localtime() will check its arg value

        _tzset()
ifdef _WIN64
        movsxd rax,_timezone
else
        mov eax,_timezone
endif
        add tmp,rax

        ; Convert this second count back into a time block structure.
        ; If localtime returns NULL, return an error.

        .ifd _localtime_s(&tb, &tmp)
            jmp err_mktime
        .endif

        ; Now must compensate for DST. The ANSI rules are to use the
        ; passed-in tm_isdst flag if it is non-negative. Otherwise,
        ; compute if DST applies. Recall that tbtemp has the time without
        ; DST compensation, but has set tm_isdst correctly.

        .if ( [rbx].tm.tm_isdst > 0 || ( [rbx].tm.tm_isdst < 0 && tb.tm_isdst > 0 ) )
ifdef _WIN64
            movsxd rax,_dstbias
else
            mov eax,_dstbias
endif
            add tmp,rax
            .ifd ( _localtime_s(&tb, &tmp) )
                jmp err_mktime
            .endif
        .endif
    .elseifd ( _gmtime_s(&tb, &tmp) )
        jmp err_mktime
    .endif

    ; tmp holds number of elapsed seconds, adjusted for local time if requested

    mov rdi,rbx
    lea rsi,tb
    mov ecx,sizeof(tb)
    rep movsb
    mov rax,tmp
    ret
    endp


mktime proc tb:ptr tm
    _make_time_t( ldr(tb), 1 )
    ret
    endp

_mkgmtime proc tb:ptr tm
    _make_time_t( ldr(tb), 0 )
    ret
    endp

    end
