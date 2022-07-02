; ISSPACE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc

    .code

isspace proc c:int_t

ifdef _WIN64
    lea     rax,_ctype
    test    byte ptr [rax+rcx*2+2],_SPACE
else
    mov     eax,c
    test    _ctype[eax*2+2],_SPACE
endif
    mov     eax,0
    setnz   al
    ret

isspace endp

    END

