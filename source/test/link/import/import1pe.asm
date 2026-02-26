;
; Dynamic base + relocation.
;

option dllimport:<msvcrt>
externdef import _dstbias:qword
externdef import printf:qword
externdef import exit:qword

.data
 format db "__ImageBase: %p, _dstbias: %d",10,0
 dreloc dq format
.code

main proc

 local call_stack[4]:qword

    mov     rax,_dstbias
    mov     r8d,[rax]
    lea     rdx,__ImageBase
    mov     rcx,dreloc
    call    printf
    xor     ecx,ecx
    call    exit

main endp

    end main
