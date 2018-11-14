; ISPRINT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc

.code

isprint proc char:SINT

    movzx eax,BYTE PTR char
    .if eax < 0x20 || eax >= 0x7F
        xor eax,eax
    .endif
    ret

isprint endp

    END

