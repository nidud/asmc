; TOUPPER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include ctype.inc

externdef _pcumap:string_t

    .code

toupper proc c:int_t
ifdef _WIN64
    movzx ecx,cl
else
    movzx ecx,byte ptr c
endif
    mov rax,_pcumap
    movzx eax,byte ptr [rax+rcx]
    ret
toupper endp

    end

