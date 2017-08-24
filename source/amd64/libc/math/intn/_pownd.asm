; _pownd() - returns the base to the exponent power
;
include intn.inc
include alloc.inc
option cstack:on

.code

_pownd proc uses rsi rdi rbx base:ptr, exponent:sdword, n:dword

local h:qword, e:ptr

    mov eax,n
    shl eax,3
    mov e,alloca(eax)
    mov ecx,n
    mov rdi,rax
    mov rsi,base
    rep movsq

    mov ebx,n
    shr ebx,1
    mov rsi,base
    lea rdi,[rsi+rbx*8] ; high product
    .if !ebx
        lea rdi,h
        inc ebx
    .endif

    .while exponent > 1

        _mulnd(rsi, e, rdi, ebx)
        dec exponent
    .endw
    mov rax,rsi
    ret

_pownd endp

    end
