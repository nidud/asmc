; STRNCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option dotname
    option win64:rsp noauto

strncpy proc dst:string_t, src:string_t, count:size_t

    mov     r10,rdi
    mov     rdi,rcx
    mov     r11,rcx
    mov     ecx,r8d
.0:
    test    ecx,ecx
    jz      .2
    dec     ecx
    mov     al,[rdx]
    mov     [rdi],al
    add     rdx,1
    add     rdi,1
    test    al,al
    jnz     .0
.1:
    rep     stosb
.2:
    mov     rdi,r10
    mov     rax,r11
    ret

strncpy endp

    end

