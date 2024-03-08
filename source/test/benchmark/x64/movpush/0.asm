
    .code

foo proc
local a:ptr, b:ptr
repeat 100
    push    a
    pop     b
endm
    ret
foo endp

    end

