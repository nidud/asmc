; WCSTOXL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; __int64 __cdecl wcstol(wchar_t *nptr, wchar_t **endptr, int ibase);
; __int64 __cdecl wcstoul(wchar_t *nptr, wchar_t **endptr, int ibase);
;
include stdlib.inc
include errno.inc

define FL_UNSIGNED  1 ; strtouq called
define FL_NEG       2 ; negative sign found
define FL_OVERFLOW  4 ; overflow occured
define FL_READDIGIT 8 ; we've read at least one correct digit

.code

wcstoxl proc private uses rsi rdi rbx strSource:wstring_t, endptr:warray_t, base:int_t, flags:int_t

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

        or  flags,FL_READDIGIT
        mul edi
        add eax,ecx
        adc edx,0
        .if ( edx )

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

wcstoxl endp

wcstol proc nptr:wstring_t, endptr:warray_t, ibase:int_t

    wcstoxl(nptr, endptr, ibase, 0)
    ret

wcstol endp

wcstoul proc nptr:wstring_t, endptr:warray_t, ibase:int_t

    wcstoxl(nptr, endptr, ibase, FL_UNSIGNED)
    ret

wcstoul endp

    end
