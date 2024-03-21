; _TTOLOWER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include ctype.inc
ifdef _UNICODE
include winnls.inc
endif
include tchar.inc

externdef _pclmap:string_t

    .code

_ttolower proc c:int_t

    ldr eax,c
    .if ( eax < 256 )

        add   rax,_pclmap
        movzx eax,byte ptr [rax]

if defined(_UNICODE) and (WINVER GE 0x0600)

    .else
        LCMapStringEx( LOCALE_NAME_USER_DEFAULT, LCMAP_LOWERCASE, &c, 1, &c, 1, 0, 0, 0 )
        mov eax,c
endif
    .endif
    ret

_ttolower endp

    end
