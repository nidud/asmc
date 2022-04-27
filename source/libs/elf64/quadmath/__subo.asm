; __SUBO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

   .code

__subo::
    mov rax,[rsi]
    sub [rdi],rax
    mov rax,[rsi+8]
    sbb [rdi+8],rax
    mov rax,rdi
    ret

    end
