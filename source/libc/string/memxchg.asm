; MEMXCHG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option dotname

memxchg proc uses rbx rdi dst:ptr, src:ptr, count:size_t

    ldr     rax,dst
    ldr     rcx,count
    ldr     rdx,src
    jmp     .1
.0:
    sub     rcx,size_t
    mov     rbx,[rdx+rcx]
    mov     rdi,[rax+rcx]
    mov     [rax+rcx],rbx
    mov     [rdx+rcx],rdi
.1:
    cmp     rcx,size_t
    jae     .0
    test    ecx,ecx
    jnz     .3
.2:
    ret
.3:
    dec     ecx
    mov     bl,[rdx+rcx]
    mov     bh,[rax+rcx]
    mov     [rax+rcx],bl
    mov     [rdx+rcx],bh
    jnz     .3
    jmp     .2

memxchg endp

    end
