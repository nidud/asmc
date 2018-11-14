; TIISWORD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ltype.inc

    .code

tiisword proc

    movzx eax,al
    mov ah,byte ptr _ltype[eax+1]

    .if !(ah & _UPPER or _LOWER or _DIGIT)

        .if al == '_'
            test al,al
        .else
            cmp al,al
        .endif
    .endif
    ret

tiisword endp

    END
