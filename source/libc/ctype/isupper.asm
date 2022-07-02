; ISUPPER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc

    .code

isupper proc c:int_t

ifdef _WIN64
    lea     rax,_ctype
    test    byte ptr [rax+rcx*2+2],_UPPER
else
    mov     eax,c
    test    _ctype[eax*2+2],_UPPER
endif
    mov     eax,0
    setnz   al
    ret

isupper endp

    end

