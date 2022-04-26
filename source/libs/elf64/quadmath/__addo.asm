; __ADDO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

   .code

__addo::

    mov rax,[rsi]
    add [rdi],rax
    mov rax,[rsi+8]
    adc [rdi+8],rax
    mov rax,rdi
    ret

    end
