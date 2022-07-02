; WCSRCHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

wcsrchr proc uses rdi s1:ptr wchar_t, wc:wchar_t

ifdef _WIN64
    mov     rdi,rcx
else
    mov     edi,s1
    mov     dx,wc
endif
    xor     eax,eax
    mov     ecx,-1
    repne   scasw
    not     ecx
    sub     rdi,2
    std
    mov     ax,dx
    repne   scasw
    mov     ax,0
    jne     @F
    lea     rax,[rdi+2]
@@:
    cld
    ret

wcsrchr endp

    end
