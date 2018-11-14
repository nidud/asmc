; _CPYND.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; _cpynd() - Copy
;
include intn.inc

option win64:rsp nosave noauto

.code

_cpynd proc dst:ptr, src:ptr, n:dword

    mov r9,rdi
    mov rdi,rcx
    xchg rsi,rdx
    mov ecx,r8d
    mov rax,rdi
    rep movsq
    mov rsi,rdx
    mov rdi,r9
    ret

_cpynd endp

    end
