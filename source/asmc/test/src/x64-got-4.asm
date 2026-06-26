
; v2.37.63

public common_data

   .data?
    common_data dd ?
   .code

main proc
    xor eax,eax
    ret
    endp

load_common proc
    mov eax,common_data[rip] ; R_X86_64_PC32
    ret
    endp

    end
