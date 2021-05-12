
;--- 128-bit <r64>::<r64> invoke arguments

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif
    .code
    option win64:auto

p1  proc a1:dword
    ret
p1  endp

f1  proc a1:oword, a2:oword
    mov rax,qword ptr a1
    mov rax,qword ptr a2
    ret
f1  endp

f2  proc a1:oword, a2:oword
    f1(rdx::rcx, r9::r8)    ; no params set
    f1(rax::rcx, r9::r8)    ; rdx
    f1(p1(0), r9::r8)       ; rcx
    f1(rax::rax, rax::rax)  ; all
    ret
f2  endp

s1  proc syscall a1:oword, a2:oword, a3:oword
    mov rax,a1
    mov rax,a2
    mov rax,a3
    ret
s1  endp

s2  proc syscall a1:oword, a2:oword, a3:oword
    s1(a1, a2, a3)                      ; no params set
    s1(rsi::rdi, rcx::rdx, r9::r8)      ; no params set
    s1(rsi::rdi, rcx::rax, r9::r8)      ; rdx
    s1(rax::rax, rax::rax, rax::rax)    ; all
    ret
s2  endp

    end
