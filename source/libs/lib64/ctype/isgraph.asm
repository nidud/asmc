; ISGRAPH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc

    .code

isgraph proc c:int_t

    mov eax,ecx
    .if al < 0x21 || al >= 0x7F

        xor eax,eax
    .endif
    ret

isgraph endp

    end
