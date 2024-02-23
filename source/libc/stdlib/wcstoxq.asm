; WCSTOXQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; __int64 __cdecl wcstoll(wchar_t *nptr, wchar_t **endptr, int ibase);
; __int64 __cdecl wcstoull(wchar_t *nptr, wchar_t **endptr, int ibase);
; __int64 __cdecl _wcstoi64(wchar_t *nptr, wchar_t **endptr, int ibase);
; __int64 __cdecl _wcstoui64(wchar_t *nptr, wchar_t **endptr, int ibase);
;

include stdlib.inc
include errno.inc

define FL_UNSIGNED  1 ; strtouq called
define FL_NEG       2 ; negative sign found
define FL_OVERFLOW  4 ; overflow occured
define FL_READDIGIT 8 ; we've read at least one correct digit

.code

wcstoxq proc private uses rsi rdi rbx strSource:wstring_t, endptr:warray_t, base:int_t, flags:int_t

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

    movzx eax,wchar_t ptr [rbx]
    .while ( ax == ' ' || ax == 9 )

        add rbx,2
        mov ax,[rbx]
    .endw

    .if ( ax == '-' || ax == '+' )

        .if ( ax == '-' )

            or flags,FL_NEG
        .endif
        add rbx,2
        mov ax,[rbx]
    .endif

    .if ( edi == 0 )

        ; determine base based on first two chars of string

        mov cx,[rbx+2]
        .if ( ax != '0' )
            mov edi,10
        .elseif ( cx == 'x' || cx == 'X' )
            mov edi,16
        .else
            mov edi,8
        .endif
    .endif

    .if ( edi == 16 && ax == '0' )

        mov ax,[rbx+2]
        .if ( ax == 'x' || ax == 'X' )
            add rbx,4
        .endif
    .endif

    xor eax,eax
    xor edx,edx

    .while 1

        movzx ecx,wchar_t ptr [rbx]
        .if ( cx >= '0' && cx <= '9' )
            sub cl,'0'
        .elseif ( cx >= 'A' && cx <= 'z' )
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
        add rbx,2
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

wcstoxq endp

wcstoll proc nptr:wstring_t, endptr:warray_t, ibase:int_t

    wcstoxq(nptr, endptr, ibase, 0)
    ret

wcstoll endp

wcstoull proc nptr:wstring_t, endptr:warray_t, ibase:int_t

    wcstoxq(nptr, endptr, ibase, FL_UNSIGNED)
    ret

wcstoull endp

_wcstoi64 proc nptr:wstring_t, endptr:warray_t, ibase:int_t

    wcstoxq(nptr, endptr, ibase, 0)
    ret

_wcstoi64 endp

_wcstoui64 proc nptr:wstring_t, endptr:warray_t, ibase:int_t

    wcstoxq(nptr, endptr, ibase, FL_UNSIGNED)
    ret

_wcstoui64 endp


    end
