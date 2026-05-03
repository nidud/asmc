;
; Dynamic base + relocation.
;
includelib msvcrt.lib

externdef __ImageBase:byte
externdef __imp__dstbias:qword
printf proto :ptr, :vararg

.data
 format db "__ImageBase: %p, _dstbias: %d",10,0
 dreloc dq format
.code

main proc

 local call_stack[4]:qword

    mov     rax,__imp__dstbias
    mov     r8d,[rax]
    lea     rdx,__ImageBase
    mov     rcx,dreloc
    call    printf
    xor     eax,eax
    ret

main endp

    end
