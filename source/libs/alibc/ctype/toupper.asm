; TOUPPER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include ctype.inc

externdef _pcumap:string_t

    .code

toupper proc c:int_t

    movzx   edi,dil
    mov     rax,_pcumap
    movzx   eax,byte ptr [rax+rdi]
    ret

toupper endp

    end

