; __SUBO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    option win64:rsp noauto

    .code

__subo proc a:ptr, b:ptr

    mov rax,[rdx+8]
    sub [rcx+8],rax
    mov rax,[rdx]
    sbb [rcx],rax
    mov rax,rcx
    ret

__subo endp

    end
