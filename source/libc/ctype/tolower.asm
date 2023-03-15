; TOLOWER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include ctype.inc

externdef _pclmap:string_t

    .code

tolower proc c:int_t
ifdef _WIN64
    movzx ecx,cl
else
    movzx ecx,byte ptr c
endif
    mov rax,_pclmap
    movzx eax,byte ptr [rax+rcx]
    ret
tolower endp

    end

