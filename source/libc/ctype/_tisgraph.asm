; ISGRAPH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc
include tchar.inc

    .code

_istgraph proc c:int_t

    ldr eax,c
    .if ( eax < 0x21 || eax >= 0x7F )
        xor eax,eax
    .else
        mov eax,1
    .endif
    ret

_istgraph endp

    end
