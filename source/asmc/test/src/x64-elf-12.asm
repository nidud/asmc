
; v2.36.08 - vararg stack

option win64:3

foo proto :ptr, :ptr, :ptr, :vararg

.code

bar proc

    local a

    nop
    foo( 0,0,0, eax,eax,eax, ecx,edx,ebx,eax )
    nop
    foo( 0,0,0, eax,eax,eax, ecx,edx,ebx,eax,eax )
    nop
    ;
    ; movsd --> movaps
    ;
    foo( 0,0,0, eax,eax,eax, ecx, xmm0,xmm0,xmm0,xmm0 )
    nop
    ret
bar endp

    end
