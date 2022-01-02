; MEMSET.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option win64:rsp noauto

memset proc uses rdi dst:ptr, chr:int_t, size:size_t

    mov     eax,edx
    mov     rdx,rcx
    mov     rdi,rcx
    mov     rcx,r8
    rep     stosb
    mov     rax,rdx
    ret

memset endp

    end
