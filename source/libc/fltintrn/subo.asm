; SUBO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

   .code

__subo proc __ccall a:ptr uint128_t, b:ptr uint128_t

    ldr     rcx,a
    ldr     rdx,b

    mov     rax,[rdx]
    sub     [rcx],rax
    mov     rax,[rdx+size_t]
    sbb     [rcx+size_t],rax
ifndef _WIN64
    mov     eax,[edx+8]
    sbb     [ecx+8],eax
    mov     eax,[edx+12]
    sbb     [ecx+12],eax
endif
    mov     rax,rcx
    ret

__subo endp

    end
