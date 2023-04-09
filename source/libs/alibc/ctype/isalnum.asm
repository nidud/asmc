; ISALNUM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc

    .code

isalnum proc c:int_t

    movzx   edi,dil
    mov     rax,_pctype
    test    byte ptr [rax+rdi*2],_UPPER or _LOWER or _DIGIT
    setnz   al
    movzx   eax,al
    ret

isalnum endp

    end

