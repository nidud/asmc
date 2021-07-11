; __ADDO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

   .code

__addo::

ifdef __UNIX__

    mov     rax,[rsi]
    add     [rdi],rax
    mov     rax,[rsi+8]
    adc     [rdi+8],rax
    mov     rax,rdi

else

    mov     rax,[rdx]
    add     [rcx],rax
    mov     rax,[rdx+8]
    adc     [rcx+8],rax
    mov     rax,rcx

endif

    ret

    end
