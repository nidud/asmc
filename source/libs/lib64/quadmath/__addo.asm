; __ADDO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

    option win64:rsp noauto

__addo proc a:ptr, b:ptr

    mov rax,[rdx]
    add [rcx],rax
    mov rax,[rdx+8]
    adc [rcx+8],rax
    mov rax,rcx
    ret

__addo endp

    end
