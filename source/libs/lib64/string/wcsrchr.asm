; WCSRCHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option win64:rsp noauto nosave

wcsrchr proc s1:ptr wchar_t, wc:wchar_t

    mov     r8,rdi
    mov     rdi,rcx
    xor     eax,eax
    mov     rcx,-1
    repne   scasw
    not     rcx
    sub     rdi,2
    std
    mov     ax,dx
    repne   scasw
    mov     ax,0
    jne     @F
    lea     rax,[rdi+2]
@@:
    cld
    mov     rdi,r8
    ret

wcsrchr endp

    end
