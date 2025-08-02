; MEMSET.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

memset proc dst:ptr, chr:int_t, size:size_t

    ldr     eax,chr
ifdef _WIN64
ifdef __UNIX__
    mov     rcx,rdx
else
    xchg    rdi,rcx
    xchg    rcx,r8
endif
else
    push    edi
    mov     edi,dst
    mov     ecx,size
endif
    mov     rdx,rdi
    rep     stosb
    mov     rax,rdx
ifdef _WIN64
ifndef __UNIX__
    mov     rdi,r8
endif
else
    pop     edi
endif
    ret

memset endp

    end
