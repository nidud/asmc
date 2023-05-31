; ISXDIGIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc

    .code

isxdigit proc c:int_t

    ldr     ecx,c
    movzx   ecx,cl
    mov     rax,_pctype
    test    byte ptr [rax+rcx*2],_HEX
    setnz   al
    movzx   eax,al
    ret

isxdigit endp

    end

