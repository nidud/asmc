
; v2.37.63: LLVM: ELF_R_X86_64_PC.s

   .code

main proc
    xor eax,eax
    ret
    endp

   .data
    db main-$ ; R_X86_64_PC8
    dw main-$ ; R_X86_64_PC16
    dd main-$ ; R_X86_64_PC32
    dq main-$ ; R_X86_64_PC64

    end
