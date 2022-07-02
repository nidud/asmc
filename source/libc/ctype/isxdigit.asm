; ISXDIGIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc

    .code

isxdigit proc c:int_t

ifdef _WIN64
    lea     rax,_ctype
    test    byte ptr [rax+rcx*2+2],_HEX
else
    mov     eax,c
    test    _ctype[eax*2+2],_HEX
endif
    mov     eax,0
    setnz   al
    ret

isxdigit endp

    end

