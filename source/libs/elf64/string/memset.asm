; MEMSET.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

memset proc dst:ptr, chr:int_t, size:size_t

    mov     rcx,rdx
    mov     eax,esi
    mov     rdx,rdi
    rep     stosb
    mov     rax,rdx
    ret

memset endp

    end
