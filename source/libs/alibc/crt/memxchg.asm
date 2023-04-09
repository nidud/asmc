; MEMXCHG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include crtl.inc

    .code

    option dotname

memxchg proc dst:string_t, src:string_t, count:size_t
.0:
    cmp     rdx,8
    jb      .1
    sub     rdx,8
    mov     rax,[rdi+rdx]
    mov     rcx,[rsi+rdx]
    mov     [rdi+rdx],rcx
    mov     [rsi+rdx],rax
    jmp     .0
.1:
    test    rdx,rdx
    jz      .3
.2:
    dec     rdx
    mov     al,[rdi+rdx]
    mov     cl,[rsi+rdx]
    mov     [rdi+rdx],cl
    mov     [rsi+rdx],al
    jnz     .2
.3:
    mov     rax,rdi
    ret

memxchg endp

    end
