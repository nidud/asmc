
;--- 128-bit <r64>::<r64> invoke arguments

    option win64:auto

    .code

s1  proc a1:oword, a2:oword, a3:oword
    mov rax,rdi
    mov rax,rdx
    mov rax,r8
    ret
s1  endp

s2  proc a1:oword, a2:oword, a3:oword

  ; added v2.34.65 - clear upper half
  ;
  ;  xor r9d,r9d
  ;  xor ecx,ecx
  ;  xor esi,esi

    s1(rdi, rdx, r8)                    ; no params set

    s1(rsi::rdi, rcx::rdx, r9::r8)      ; no params set
    s1(rsi::rdi, rcx::rax, r9::r8)      ; rdx
    s1(rax::rax, rax::rax, rax::rax)    ; all
    ret
s2  endp

    end
