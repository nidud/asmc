
    .code

foo proc
local a:ptr, b:ptr
repeat 100
    mov     rax,a
    mov     b,rax
endm
    ret
foo endp

    end

