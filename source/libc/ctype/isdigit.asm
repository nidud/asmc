; ISDIGIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc

    .code

isdigit proc c:int_t

    ldr     ecx,c
    movzx   ecx,cl
    mov     rax,_pctype
    test    byte ptr [rax+rcx*2],_DIGIT
    setnz   al
    movzx   eax,al
    ret

isdigit endp

    end

