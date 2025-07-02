; _TSTRTOQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; __int64 _strtoi64(char *nptr, char **endptr, int ibase);
; __int64 strtoll(char *nptr, char **endptr, int ibase);
; unsigned __int64 _strtoui64(char *nptr, char **endptr, int ibase);
; unsigned __int64 strtoull(char *nptr, char **endptr, int ibase);
; __int64 wcstoll(wchar_t *nptr, wchar_t **endptr, int ibase);
; __int64 _wcstoi64(wchar_t *nptr, wchar_t **endptr, int ibase);
; unsigned __int64 wcstoull(wchar_t *nptr, wchar_t **endptr, int ibase);
; unsigned __int64 _wcstoui64(wchar_t *nptr, wchar_t **endptr, int ibase);
;
include stdlib.inc
include errno.inc
include tchar.inc

define FL_UNSIGNED  1 ; strtouq called
define FL_NEG       2 ; negative sign found
define FL_OVERFLOW  4 ; overflow occured
define FL_READDIGIT 8 ; we've read at least one correct digit

.code

strtoxq proc private uses rsi rdi rbx strSource:tstring_t, endptr:tarray_t, base:int_t, flags:int_t

   .new maxval:size_t

    ldr rbx,strSource
    ldr rsi,endptr
    ldr edi,base

    .if ( rsi )

        mov [rsi],rbx ; store beginning of string
    .endif

    .if ( rbx == NULL || ( edi != 0 && ( edi < 2 || edi > 36 ) ) )

        _set_errno(EINVAL)
        .return( 0 )
    .endif

    movzx eax,tchar_t ptr [rbx]
    .while ( eax == ' ' || eax == 9 )

        add rbx,tchar_t
        movzx eax,tchar_t ptr [rbx]
    .endw

    .if ( eax == '-' || eax == '+' )

        .if ( eax == '-' )

            or flags,FL_NEG
        .endif
        add rbx,tchar_t
        movzx eax,tchar_t ptr [rbx]
    .endif

    .if ( edi == 0 )

        ; determine base based on first two chars of string

        movzx ecx,tchar_t ptr [rbx+tchar_t]
        .if ( eax != '0' )
            mov edi,10
        .elseif ( ecx == 'x' || ecx == 'X' )
            mov edi,16
        .else
            mov edi,8
        .endif
    .endif

    .if ( edi == 16 && eax == '0' )

        movzx eax,tchar_t ptr [rbx+tchar_t]
        .if ( eax == 'x' || eax == 'X' )
            add rbx,2*tchar_t
        .endif
    .endif

    xor eax,eax
    xor edx,edx

    .while 1

        movzx ecx,tchar_t ptr [rbx]
        .if ( ecx >= '0' && ecx <= '9' )
            sub cl,'0'
        .elseif ( ecx >= 'A' && ecx <= 'z' )
            .break .if ( cl > 'Z' && cl < 'a' )
            and cl,not 0x20
            sub cl,'A'-10
        .else
            .break
        .endif
        .break .if ecx >= edi

        or flags,FL_READDIGIT

ifdef _WIN64
        mov maxval,rax
else
        mov maxval,edx
        .if ( !edx )
endif
            mul rdi
ifndef _WIN64
        .else
            push    ecx
            push    eax
            push    edx
            pop     eax
            mul     edi
            mov     ecx,eax
            pop     eax
            mul     edi
            add     edx,ecx
            pop     ecx
        .endif
endif
        add rax,rcx
ifndef _WIN64
        adc edx,0
        .if ( edx < maxval )
else
        .if ( rax < maxval )
endif
            or flags,FL_OVERFLOW
            .break .if ( !rsi )
        .endif
        add rbx,tchar_t
    .endw

    .if ( !( flags & FL_READDIGIT ) )

        ; no number there

       .return
    .endif

    .if ( rsi )

        mov [rsi],rbx
    .endif

    mov ebx,flags
    .if ( !( ebx & FL_UNSIGNED ) && !( ebx & FL_OVERFLOW ) )

        .if ( ebx & FL_NEG )
ifdef _WIN64
            mov rcx,-_I64_MIN
            .if ( rax > rcx )
else
            .if ( edx > HIGH32(-_I64_MIN) || ( edx == HIGH32(-_I64_MIN) && eax > LOW32(-_I64_MIN) ) )
endif
                or ebx,FL_OVERFLOW
            .endif
        .else
ifdef _WIN64
            mov rcx,_I64_MAX
            .if ( rax > rcx )
else
            .if ( edx > HIGH32(_I64_MAX) || ( edx == HIGH32(_I64_MAX) && eax > LOW32(_I64_MAX) ) )
endif
                or ebx,FL_OVERFLOW
            .endif
        .endif
    .endif

    .if ( ebx & FL_OVERFLOW  )

        ; overflow occurred

        _set_errno(ERANGE)

        .if ( ebx & FL_UNSIGNED )
ifdef _WIN64
            mov rax,_UI64_MAX
else
            mov eax,LOW32(_UI64_MAX)
            mov edx,HIGH32(_UI64_MAX)
endif
        .elseif ( ebx & FL_NEG )
ifdef _WIN64
            mov rax,_I64_MIN
else
            mov eax,LOW32(_I64_MIN)
            mov edx,HIGH32(_I64_MIN)
endif
        .else
ifdef _WIN64
            mov rax,_I64_MAX
else
            mov eax,LOW32(_I64_MAX)
            mov edx,HIGH32(_I64_MAX)
endif
        .endif
    .endif

    .if ( ebx & FL_NEG )
ifdef _WIN64
        neg rax
else
        neg edx
        neg eax
        sbb edx,0
endif
    .endif
    ret

strtoxq endp

_tcstoi64 proc nptr:tstring_t, endptr:tarray_t, ibase:int_t

    strtoxq(nptr, endptr, ibase, 0)
    ret

_tcstoi64 endp

_tcstoll proc nptr:tstring_t, endptr:tarray_t, ibase:int_t

    _tcstoi64(nptr, endptr, ibase)
    ret

_tcstoll endp

_tcstoui64 proc nptr:tstring_t, endptr:tarray_t, ibase:int_t

    strtoxq(nptr, endptr, ibase, FL_UNSIGNED)
    ret

_tcstoui64 endp

_tcstoull proc nptr:tstring_t, endptr:tarray_t, ibase:int_t

    _tcstoui64(nptr, endptr, ibase)
    ret

_tcstoull endp

    end
