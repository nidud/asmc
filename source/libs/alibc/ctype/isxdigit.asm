; ISXDIGIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc

    .code

isxdigit proc c:int_t

    movzx   edi,dil
    mov     rax,_pctype
    test    byte ptr [rax+rdi*2],_HEX
    setnz   al
    movzx   eax,al
    ret

isxdigit endp

    end

