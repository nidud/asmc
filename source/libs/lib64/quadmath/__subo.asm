; __SUBO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

   .code

__subo::

ifdef __UNIX__

    mov     rax,[rsi]
    sub     [rdi],rax
    mov     rax,[rsi+8]
    sbb     [rdi+8],rax
    mov     rax,rdi

else

    mov     rax,[rdx]
    sub     [rcx],rax
    mov     rax,[rdx+8]
    sbb     [rcx+8],rax
    mov     rax,rcx

endif

    ret

    end
