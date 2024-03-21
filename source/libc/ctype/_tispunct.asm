; _TISPUNCT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc
include tchar.inc

    .code

_istpunct proc c:int_t

    ldr eax,c
    .if ( eax < 256 )

        add     eax,eax
        add     rax,_pctype
        movzx   eax,byte ptr [rax]
        test    eax,_PUNCT
        setnz   al
    .else
        xor     eax,eax
    .endif
    ret

_istpunct endp

    end

