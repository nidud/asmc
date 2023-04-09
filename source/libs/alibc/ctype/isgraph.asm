; ISGRAPH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc

    .code

isgraph proc c:int_t

    mov eax,1
    .if ( dil < 0x21 || dil >= 0x7F )
        xor eax,eax
    .endif
    ret

isgraph endp

    end
