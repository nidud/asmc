; MEMSET.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

memset proc uses rdi dst:ptr, chr:int_t, size:size_t

ifdef _WIN64
    mov     eax,edx
    mov     rdx,rcx
    mov     rdi,rcx
    mov     rcx,r8
else
    mov     edi,dst
    mov     eax,chr
    mov     ecx,size
    mov     edx,edi
endif
    rep     stosb
    mov     rax,rdx
    ret

memset endp

    end
