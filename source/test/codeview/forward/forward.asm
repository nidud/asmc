
includelib libc.lib

; forward declaration

asym_t typedef ptr asym

asym struct
next asym_t ?
prev asym_t ?
asym ends

.code

main proc

    local sym[2]:asym

    xor eax,eax
    lea rdx,sym
    lea rcx,sym[sizeof(asym)]
    mov sym.prev,rax
    mov sym.next,rcx
    mov [rcx].asym.prev,rdx
    mov [rcx].asym.next,rax
    ret

main endp

    end
