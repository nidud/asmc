; ISLEADBYTE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc

    .code

isleadbyte proc wc:int_t

ifdef _WIN64
    lea     rax,_ctype
    test    wchar_t ptr [rax+rcx*2+2],_LEADBYTE
else
    mov     eax,wc
    test    _ctype[eax*2+2],_LEADBYTE
endif
    mov     eax,0
    setnz   al
    ret

isleadbyte endp

    end

