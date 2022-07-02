; WCSNCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option dotname

wcsncpy proc uses rdi dst:wstring_t, src:wstring_t, count:size_t

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
    mov     ax,[rdx]
    mov     [rdi],ax
    add     rdx,2
    add     rdi,2
    test    ax,ax
    jnz     .0
    rep     stosw
.1:
ifdef _WIN64
    mov     rax,r11
else
    mov     eax,dst
endif
    ret

wcsncpy endp

    end
