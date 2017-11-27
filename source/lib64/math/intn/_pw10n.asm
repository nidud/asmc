; _pw10n() - returns the base to the power of 10
;
include intn.inc
include malloc.inc
option cstack:on

.code

_pw10n proc uses rsi rdi rbx base:ptr, exponent:sdword, n:dword

local h:qword, e:ptr

    mov eax,n
    shl eax,3
    mov e,alloca(eax)
    mov ecx,n
    mov rdi,rax
    xor eax,eax
    rep stosq
    mov rax,e
    mov byte ptr [rax],10

    mov ebx,n
    shr ebx,1
    mov rsi,base
    lea rdi,[rsi+rbx*8] ; high product
    .if !ebx
        lea rdi,h
        inc ebx
    .endif

    .while exponent > 0

        _mulnd(rsi, e, rdi, ebx)
        dec exponent
    .endw
    mov rax,rsi
    ret

_pw10n endp

    end
