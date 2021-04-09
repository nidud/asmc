
option win64:rbp save auto

foo_1 proto :qword, :qword, :qword, :qword, :qword, :qword
foo_2 proto :qword, :qword, :qword, :qword, :qword, :qword

    .code

main proc uses rsi rdi

    foo_1(1,2,3,4,5,6)
    ret

main endp

foo_1 proc private uses rsi rdi rbx a:qword, b:qword, c:qword, d:qword, e:qword, f:qword
repeat 6
    foo_2(a,b,c,d,e,f)
    sub rax,a
    sub rax,b
    sub rax,c
    sub rax,d
    sub rax,e
    sub rax,f
endm
    ret

foo_1 endp

foo_2 proc private a:qword, b:qword, c:qword, d:qword, e:qword, f:qword
repeat 6
    mov rax,a
    add rax,b
    add rax,c
    add rax,d
    add rax,e
    add rax,f
endm
    ret

foo_2 endp

    END
