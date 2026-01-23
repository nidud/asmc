
; v2.37.65: label[rip], label - $

   .code

main proc
    mov rax,A[rip]  ; 3, R_X86_64_PC32, A - 4
    mov rcx,B[rip]  ; A, R_X86_64_PC32, B - 4
    ret
    endp

   .data
    A dq main       ; 0, R_X86_64_64,   main + 0
    B dq main-$     ; 8, R_X86_64_PC64, main + 0
    end
