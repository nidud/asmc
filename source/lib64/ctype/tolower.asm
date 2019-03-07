; TOLOWER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include ctype.inc
include winnls.inc

    .code

tolower proc char:SINT

    mov eax,ecx

    .repeat

        .break .if ( al < 'A' )

        .if ( al <= 'Z' )

            add al,'a'-'A'
            .break
        .endif

        .break .if ( al >= 'a' && al <= 'z' )

if WINVER GE 0x0600
        LCMapStringEx(LOCALE_NAME_USER_DEFAULT,
            LCMAP_LOWERCASE, &char, 1, &char, 1, 0, 0, 0)
        mov eax,char
endif
    .until 1
    ret

tolower endp

    end

