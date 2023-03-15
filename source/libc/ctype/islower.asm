; ISLOWER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc

    .code

islower proc c:int_t
ifndef _WIN64
    movzx   ecx,byte ptr c
else
    movzx   ecx,cl
endif
    mov     rax,_pctype
    test    byte ptr [rax+rcx*2],_LOWER
    setnz   al
    movzx   eax,al
    ret
islower endp

    end

