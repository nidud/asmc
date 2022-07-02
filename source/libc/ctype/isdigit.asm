; ISDIGIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc

    .code

isdigit proc c:int_t

ifdef _WIN64
    lea     rax,_ctype
    test    word ptr [rax+rcx*2+2],_DIGIT
else
    mov     eax,c
    test    _ctype[eax*2+2],_DIGIT
endif
    mov     eax,0
    setnz   al
    ret

isdigit endp

    end

