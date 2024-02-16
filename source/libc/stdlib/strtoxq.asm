; STRTOXQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; __int64 __cdecl _strtoi64(char *nptr, char **endptr, int ibase);
; __int64 __cdecl strtoll(char *nptr, char **endptr, int ibase);
; __int64 __cdecl _strtoui64(char *nptr, char **endptr, int ibase);
; __int64 __cdecl strtoull(char *nptr, char **endptr, int ibase);
;
include stdlib.inc
include errno.inc

define FL_UNSIGNED  1 ; strtouq called
define FL_NEG       2 ; negative sign found
define FL_OVERFLOW  4 ; overflow occured
define FL_READDIGIT 8 ; we've read at least one correct digit

.code

strtoxq proc private uses rsi rdi rbx strSource:string_t, endptr:array_t, base:int_t, flags:int_t

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

    movzx eax,byte ptr [rbx]
    .while ( al == ' ' || al == 9 )

        inc rbx
        mov al,[rbx]
    .endw

    .if ( al == '-' || al == '+' )

        .if ( al == '-' )

            or flags,FL_NEG
        .endif
        inc rbx
        mov al,[rbx]
    .endif

    .if ( edi == 0 )

        ; determine base based on first two chars of string

        mov cl,[rbx+1]
        .if ( al != '0' )
            mov edi,10
        .elseif ( cl == 'x' || cl == 'X' )
            mov edi,16
        .else
            mov edi,8
        .endif
    .endif

    .if ( edi == 16 && al == '0' )

        mov al,[rbx+1]
        .if ( al == 'x' || al == 'X' )
            add rbx,2
        .endif
    .endif

    xor eax,eax
    xor edx,edx

    .while 1

        movzx ecx,byte ptr [rbx]
        .if ( cl >= '0' && cl <= '9' )
            sub cl,'0'
        .elseif ( cl >= 'A' && cl <= 'z' )
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
        add rbx,1
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

_strtoi64 proc nptr:string_t, endptr:array_t, ibase:int_t

    strtoxq(nptr, endptr, ibase, 0)
    ret

_strtoi64 endp

strtoll proc nptr:string_t, endptr:array_t, ibase:int_t

    _strtoi64(nptr, endptr, ibase)
    ret

strtoll endp

_strtoui64 proc nptr:string_t, endptr:array_t, ibase:int_t

    strtoxq(nptr, endptr, ibase, FL_UNSIGNED)
    ret

_strtoui64 endp

strtoull proc nptr:string_t, endptr:array_t, ibase:int_t

    _strtoui64(nptr, endptr, ibase)
    ret

strtoull endp

    end
