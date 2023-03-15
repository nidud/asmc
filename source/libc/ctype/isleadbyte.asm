; ISLEADBYTE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc

    .code

isleadbyte proc wc:int_t
ifndef _WIN64
    movzx   ecx,byte ptr wc
else
    movzx   ecx,cl
endif
    mov     rax,_pctype
    test    word ptr [rax+rcx*2],_LEADBYTE
    setnz   al
    movzx   eax,al
    ret
isleadbyte endp

    end

