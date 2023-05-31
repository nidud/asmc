; ISCNTRL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc

    .code

iscntrl proc c:int_t

    ldr     ecx,c
    movzx   ecx,cl
    mov     rax,_pctype
    test    byte ptr [rax+rcx*2],_CONTROL
    setnz   al
    movzx   eax,al
    ret

iscntrl endp

    end

