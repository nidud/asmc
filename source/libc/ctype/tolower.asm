; TOLOWER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include ctype.inc
include winnls.inc

    .code

tolower proc c:int_t

ifdef _WIN64
    mov eax,ecx
else
    mov eax,c
endif

    .return .if ( al < 'A' )

    .if ( al <= 'Z' )

        add al,'a'-'A'
       .return
    .endif

    .return .if ( al >= 'a' && al <= 'z' )

if WINVER GE 0x0600
    LCMapStringEx( LOCALE_NAME_USER_DEFAULT, LCMAP_LOWERCASE, &c, 1, &c, 1, 0, 0, 0 )
    mov eax,c
endif
    ret

tolower endp

    end

