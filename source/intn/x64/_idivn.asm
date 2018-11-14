; _IDIVN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; _idivn() - Signed Divide
;
; Signed binary division of dividend by source.
; Note: The quotient is stored in "dividend".
;
include intn.inc

option win64:rsp nosave noauto

.code

_idivn proc uses rsi rdi rbx r12 dividend:ptr, divisor:ptr, reminder:ptr, n:dword

    mov rsi,rdx
    mov rdi,rcx
    mov r12,r8
    mov ebx,r9d

    mov rax,[rdi+rbx*8-8]
    test rax,rax
    .ifs
        _negnd(rdi, ebx)
        mov rax,[rsi+rbx*8-8]
        test rax,rax
        .ifs
            _negnd(rsi, ebx)
            _divnd(rdi, rsi, r12, ebx)
            _negnd(rsi, ebx)
        .else
            _divnd(rdi, rsi, r12, ebx)
            _negnd(rdi, ebx)
        .endif
    .else
        mov rax,[rsi+rbx*8-8]
        test rax,rax
        .ifs
            _negnd(rsi, ebx)
            _divnd(rdi, rsi, r12, ebx)
            _negnd(rsi, ebx)
            _negnd(rdi, ebx)
        .else
            _divnd(rdi, rsi, r12, ebx)
        .endif
    .endif
    ret

_idivn endp

    end
