; TOLOWER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include ctype.inc

    .code

tolower proc c:int_t

    ldr     ecx,c
    movzx   ecx,cl
    mov     rax,_pclmap
    movzx   eax,byte ptr [rax+rcx]
    ret

tolower endp

    end

