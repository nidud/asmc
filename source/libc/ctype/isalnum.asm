; ISALNUM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc

    .code

isalnum proc c:int_t

ifdef _WIN64
    lea     rax,_ctype
    test    byte ptr [rax+rcx*2+2],_UPPER or _LOWER or _DIGIT
else
    mov     eax,c
    test    _ctype[eax*2+2],_UPPER or _LOWER or _DIGIT
endif
    mov     eax,0
    setnz   al
    ret

isalnum endp

    end

