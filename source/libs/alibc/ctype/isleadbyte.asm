; ISLEADBYTE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc

    .code

isleadbyte proc wc:int_t

    movzx   edi,dil
    mov     rax,_pctype
    test    word ptr [rax+rdi*2],_LEADBYTE
    setnz   al
    movzx   eax,al
    ret

isleadbyte endp

    end

