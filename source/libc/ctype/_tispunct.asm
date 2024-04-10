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
    movzx eax,_tal
ifdef _UNICODE
    .if ( eax < 256 )
endif
        mov   rcx,_pctype
        test  byte ptr [rcx+rax*2],_PUNCT
        setnz al
ifdef _UNICODE
    .else
        xor     eax,eax
    .endif
endif
    ret

_istpunct endp

    end

