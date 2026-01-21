
; v2.37.63: extern :ABS

extern D:ABS
extern W:ABS
extern B:ABS

   .code

main proc
    xor eax,eax
    ret
    endp

   .data
    dd D ; R_X86_64_32
    dw W ; R_X86_64_16
    db B ; R_X86_64_8
    end
