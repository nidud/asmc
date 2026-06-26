
; v2.37.66: rip fixup

extern var:dword
named_func proto

.code

main proc
    mov eax,var[rip] ; IMAGE_REL_AMD64_REL32
    ret
    endp

test_rel32_func proc
    call named_func  ; IMAGE_REL_AMD64_REL32
    endp

test_rel32_data proc
    lea rax,named_data[rip] ; IMAGE_REL_AMD64_REL32
    endp

test_addr64 proc
    dq named_data ; IMAGE_REL_AMD64_ADDR64
    endp

.data
 named_data dq 53

    end
