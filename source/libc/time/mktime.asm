; MKTIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc

    .data
    .code

ChkAdd macro dest, src1, src2
    exitm<( ((src1 !>= 0) && (src2 !>= 0) && (dest !< 0)) || ((src1 !< 0) && (src2 !< 0) && (dest !>= 0)) )>
    endm

ChkMul macro dest, src1, src2
    .if src1
        mov eax,dest
        xor edx,edx
        div src1
        cmp eax,src2
        mov eax,0
        setne al
    .else
        xor eax,eax
    .endif
    retm<eax>
    endm

_make_time_t proc private uses rsi rdi rbx tb:ptr tm, ultflag:int_t

  local tmptm1:long_t, tmptm2:long_t, tmptm3:long_t
  local tbtemp:ptr tm

    ldr rcx,tb
    mov rdi,rcx
    mov eax,[rdi].tm.tm_year

    .if ( ( eax < _BASE_YEAR - 1) || ( eax > _MAX_YEAR + 1) )
        jmp err_mktime
    .endif
    mov tmptm1,eax

    mov eax,[rdi].tm.tm_mon
    mov ecx,12
    xor edx,edx
    div ecx
    mov tmptm2,eax

    .if ( eax != 0 )

        add tmptm1,eax
        mov [rdi].tm.tm_mon,edx

        .ifs ( edx < 0 )
            add [rdi].tm.tm_mon,12
            dec tmptm1
        .endif
        .if ( (tmptm1 < _BASE_YEAR - 1) || (tmptm1 > _MAX_YEAR + 1) )
            jmp err_mktime
        .endif
    .endif

    mov eax,[rdi].tm.tm_mon
    lea rdx,_days
    mov ecx,[rdx+rax]

    .if ( !(tmptm1 & 3) && (eax > 1) )
        inc ecx
    .endif
    mov tmptm2,ecx

    mov eax,tmptm1
    mov ecx,eax
    sub eax,_BASE_YEAR
    imul eax,eax,365
    dec ecx
    shr ecx,2
    add eax,ecx
    sub eax,_LEAP_YEAR_ADJUST

    add eax,tmptm2
    mov tmptm3,eax

    mov ecx,[rdi].tm.tm_mday
    mov tmptm2,ecx
    lea edx,[rcx+rax]
    mov tmptm1,edx
    .ifs ( ChkAdd(edx, eax, ecx) )
        jmp err_mktime
    .endif

    imul eax,tmptm1,24
    mov tmptm2,eax
    .if ( ChkMul(tmptm2, tmptm1, 24) )
        jmp err_mktime
    .endif

    mov eax,[rdi].tm.tm_hour
    mov tmptm3,eax
    add eax,tmptm2
    mov tmptm1,eax
    .if ( ChkAdd(tmptm1, tmptm2, tmptm3) )
        jmp err_mktime
    .endif

    imul eax,tmptm1,60
    mov tmptm2,eax
    .if ( ChkMul(tmptm2, tmptm1, 60) )
        jmp err_mktime
    .endif

    mov eax,[rdi].tm.tm_min
    mov tmptm3,eax
    add eax,tmptm2
    mov tmptm1,eax
    .if ( ChkAdd(tmptm1, tmptm2, tmptm3) )
        jmp err_mktime
    .endif

    imul eax,tmptm1,60
    mov tmptm2,eax
    .if ( ChkMul(tmptm2, tmptm1, 60) )
        jmp err_mktime
    .endif

    mov eax,[rdi].tm.tm_sec
    mov tmptm3,eax
    add eax,tmptm2
    mov tmptm1,eax
    .if ( ChkAdd(tmptm1, tmptm2, tmptm3) )
        jmp err_mktime
    .endif

    .if ( ultflag )

        _tzset()
        add tmptm1,_timezone

        mov rsi,localtime(&tmptm1)
        .if ( rax == NULL )
            jmp err_mktime
        .endif

        .if ( ( [rdi].tm.tm_isdst > 0) || ( ( [rdi].tm.tm_isdst < 0 ) && ( [rsi].tm.tm_isdst > 0 ) ) )
            sub tmptm1,3600
            mov rsi,localtime(&tmptm1)
        .endif

    .else
        .if ( gmtime( &tmptm1 ) == NULL )
            jmp err_mktime
        .endif
        mov rsi,rax
    .endif

    mov ecx,sizeof(tm)
    rep movsb
   .return tmptm1

err_mktime:

    .return (-1)

_make_time_t endp


mktime proc tb:ptr tm

    ldr rcx,tb
   .return( _make_time_t( rcx, 1 ) )
mktime endp

_mkgmtime proc tb:ptr tm

    ldr rcx,tb
   .return( _make_time_t( rcx, 0 ) )
_mkgmtime endp

    end
