; MKTIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include errno.inc

    .code

ChkAdd macro d, a, b
    .ifs ( (a >= 0 && b >= 0 && d < 0) || (a < 0 && b < 0 && d >= 0) )
        .return( -1 )
    .endif
    exitm<>
    endm

ChkMul macro d, a, i
    .if ( a )
        mov eax,d
        cdq
        idiv a
        .if ( eax != i )
            .return( -1 )
        .endif
    .endif
    exitm<>
    endm

_make_time_t proc private uses rsi rdi rbx tp:ptr tm, ultflag:int_t

   .new tb:tm
   .new tmp:long_t

    ldr rbx,tp

    .if ( rbx == NULL )
        .return( _set_errno(EINVAL) )
    .endif

    mov eax,[rbx].tm.tm_year
    .ifs ( ( eax < _BASE_YEAR - 1 ) || ( eax > _MAX_YEAR + 1 ) )

       .return( -1 )
    .endif
    mov esi,eax
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
        .ifs ( ( esi < _BASE_YEAR - 1 ) || ( esi > _MAX_YEAR + 1 ) )

           .return( -1 )
        .endif
    .endif
    mov [rbx].tm.tm_mon,edi

    ; ESI: number of elapsed years
    ;
    ; Calculate days elapsed minus one, in the given year, to the given
    ; month. Check for leap year and adjust if necessary.

    lea rdx,_days
    mov ecx,[rdx+rdi*4]
    .if ( !( esi & 3 ) && edi > 1 )
        inc ecx
    .endif

    ; Calculate elapsed days since base date (midnight, 1/1/70, UTC)
    ;
    ; 365 days for each elapsed year since 1970, plus one more day for
    ; each elapsed leap year. no danger of overflow because of the range
    ; check (above) on ESI.

    lea eax,[rsi-_BASE_YEAR]
    imul edi,eax,365
    lea eax,[rsi-1]
    shr eax,2
    add edi,eax
    sub edi,_LEAP_YEAR_ADJUST

    ; elapsed days to current month (still no possible overflow)

    add edi,ecx

    ; elapsed days to current date. overflow is now possible.

    mov ecx,[rbx].tm.tm_mday
    lea rsi,[rdi+rcx]

    ChkAdd(esi, edi, ecx)

    ; ESI: number of elapsed days
    ;
    ; Calculate elapsed hours since base date

    imul ecx,esi,24

    ChkMul(ecx, esi, 24)

    mov edi,[rbx].tm.tm_hour
    lea rsi,[rdi+rcx]

    ChkAdd(esi, ecx, edi)

    ; ESI: number of elapsed hours
    ;
    ; Calculate elapsed minutes since base date

    imul ecx,esi,60

    ChkMul(ecx, esi, 60)

    mov edi,[rbx].tm.tm_min
    lea rsi,[rdi+rcx]

    ChkAdd(esi, ecx, edi)

    ; ESI: number of elapsed minutes
    ;
    ; Calculate elapsed seconds since base date

    imul ecx,esi,60

    ChkMul(ecx, esi, 60)

    mov edi,[rbx].tm.tm_sec
    lea rsi,[rdi+rcx]

    ChkAdd(esi, ecx, edi)

    ; ESI: number of elapsed seconds

    mov tmp,esi

    .if ( ultflag )

        ; Adjust for timezone. No need to check for overflow since
        ; localtime() will check its arg value

        _tzset()

        add tmp,_timezone

        ; Convert this second count back into a time block structure.
        ; If localtime returns NULL, return an error.

        .ifd ( _localtime32_s(&tb, &tmp) )

            .return( -1 )
        .endif

        ; Now must compensate for DST. The ANSI rules are to use the
        ; passed-in tm_isdst flag if it is non-negative. Otherwise,
        ; compute if DST applies. Recall that tbtemp has the time without
        ; DST compensation, but has set tm_isdst correctly.

        .if ( [rbx].tm.tm_isdst > 0 || ( [rbx].tm.tm_isdst < 0 && tb.tm_isdst > 0 ) )

            add tmp,_dstbias
            .ifd ( _localtime32_s(&tb, &tmp) )

                .return( -1 )
            .endif
        .endif

    .elseifd ( _gmtime32_s(&tb, &tmp) )

        .return( -1 )
    .endif

    ; tmp holds number of elapsed seconds, adjusted for local time if requested

    mov rdi,rbx
    lea rsi,tb
    mov ecx,sizeof(tb)
    rep movsb
    mov eax,tmp
    ret

_make_time_t endp


mktime proc tb:ptr tm

    ldr rcx,tb

    _make_time_t( rcx, 1 )
    ret

mktime endp

_mkgmtime proc tb:ptr tm

    ldr rcx,tb

    _make_time_t( rcx, 0 )
    ret

_mkgmtime endp

    end
