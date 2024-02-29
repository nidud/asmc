; MEMXCHG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option dotname

memxchg proc uses rsi rbx dst:ptr, src:ptr, count:size_t

    ldr     rbx,count
    ldr     rcx,dst
    ldr     rdx,src
.0:
    cmp     rbx,size_t
    jb      .1
    sub     rbx,size_t
    mov     rax,[rcx+rbx]
    mov     rsi,[rdx+rbx]
    mov     [rcx+rbx],rsi
    mov     [rdx+rbx],rax
    jmp     .0
.1:
    test    rbx,rbx
    jz      .3
.2:
    dec     rbx
    mov     al,[rcx+rbx]
    mov     ah,[rdx+rbx]
    mov     [rcx+rbx],ah
    mov     [rdx+rbx],al
    jnz     .2
.3:
    mov     rax,rcx
    ret

memxchg endp

    end
