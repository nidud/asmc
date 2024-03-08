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
    ldr     rdx,src
    ldr     rcx,count
    jmp     .2
.1:
    sub     rcx,size_t
    mov     rbx,[rdx+rcx]
    mov     rdi,[rax+rcx]
    mov     [rax+rcx],rbx
    mov     [rdx+rcx],rdi
.2:
    cmp     rcx,size_t
    jae     .1
    test    ecx,ecx
    jz      .4
.3:
    dec     ecx
    mov     bl,[rdx+rcx]
    mov     bh,[rax+rcx]
    mov     [rax+rcx],bl
    mov     [rdx+rcx],bh
    jnz     .3
.4:
    ret

memxchg endp

    end
