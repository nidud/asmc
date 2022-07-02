; STRNCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option dotname

strncpy proc uses rdi dst:string_t, src:string_t, count:size_t

ifdef _WIN64
    mov     rdi,rcx
    mov     r11,rcx
    mov     ecx,r8d
else
    mov     edi,dst
    mov     edx,src
    mov     ecx,count
endif
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
ifdef _WIN64
    mov     rax,r11
else
    mov     eax,dst
endif
    ret

strncpy endp

    end

