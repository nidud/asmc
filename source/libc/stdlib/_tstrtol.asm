; _TSTRTOL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; __int64 strtol(char *nptr, char **endptr, int ibase);
; __int64 wcstol(wchar_t *nptr, wchar_t **endptr, int ibase);
; unsigned __int64 strtoul(char *nptr, char **endptr, int ibase);
; unsigned __int64 wcstoul(wchar_t *nptr, wchar_t **endptr, int ibase);
;
include stdlib.inc
include errno.inc
include tchar.inc

define FL_UNSIGNED  1 ; strtouq called
define FL_NEG       2 ; negative sign found
define FL_OVERFLOW  4 ; overflow occured
define FL_READDIGIT 8 ; we've read at least one correct digit

.code

strtoxl proc private uses rsi rdi rbx strSource:tstring_t, endptr:tarray_t, base:int_t, flags:int_t

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

        or  flags,FL_READDIGIT
        mul edi
        add eax,ecx
        adc edx,0
        .if ( edx )

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
            .if ( eax > -LONG_MIN )
                or ebx,FL_OVERFLOW
            .endif
        .elseif ( eax > LONG_MAX )
            or ebx,FL_OVERFLOW
        .endif
    .endif

    .if ( ebx & FL_OVERFLOW  )

        ; overflow occurred

        _set_errno(ERANGE)
        .if ( ebx & FL_UNSIGNED )
            mov eax,ULONG_MAX
        .elseif ( ebx & FL_NEG )
            mov eax,-LONG_MIN
        .else
            mov eax,LONG_MAX
        .endif
    .endif
    .if ( ebx & FL_NEG )
        neg eax
    .endif
    ret

strtoxl endp

_tcstol proc nptr:tstring_t, endptr:tarray_t, ibase:int_t

    strtoxl(nptr, endptr, ibase, 0)
    ret

_tcstol endp

_tcstoul proc nptr:tstring_t, endptr:tarray_t, ibase:int_t

    strtoxl(nptr, endptr, ibase, FL_UNSIGNED)
    ret

_tcstoul endp

    end
