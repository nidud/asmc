; TOWUPPER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include ctype.inc
include winnls.inc

    .code

towupper proc char:wchar_t

    mov eax,ecx

    .repeat

        .break .if ( ax <= 'Z' )

        .if ( ax >= 'a' && ax <= 'z' )

            sub ax,'a'-'A'
            .break
        .endif

if WINVER GE 0x0600
        LCMapStringEx(LOCALE_NAME_USER_DEFAULT,
            LCMAP_UPPERCASE, &char, 1, &char, 1, 0, 0, 0)
        movzx eax,char
endif
    .until 1
    ret

towupper endp

    end

