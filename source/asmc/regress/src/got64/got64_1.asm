
; v2.37.63: _GLOBAL_OFFSET_TABLE_

.code

main proc
    lea ebx,_GLOBAL_OFFSET_TABLE_[rip] ; R_X86_64_GOTPC32
    xor eax,eax
    ret
    endp

    end
