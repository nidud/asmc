; TOLOWER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include ctype.inc

externdef _pclmap:string_t

    .code

tolower proc c:int_t

    movzx   edi,dil
    mov     rax,_pclmap
    movzx   eax,byte ptr [rax+rdi]
    ret

tolower endp

    end

