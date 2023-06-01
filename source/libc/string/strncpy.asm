; STRNCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option dotname

strncpy proc uses rdi rbx dst:string_t, src:string_t, count:size_t

    ldr     rdi,dst
    ldr     rcx,count
    ldr     rdx,src
    mov     rbx,rdi
.0:
    test    ecx,ecx
    jz      .1
    dec     ecx
    mov     al,[rdx]
    mov     [rdi],al
    add     rdx,1
    add     rdi,1
    test    al,al
    jnz     .0
    rep     stosb
.1:
    mov     rax,rbx
    ret

strncpy endp

    end

