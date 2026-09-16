
; v2.39.11 -- return type from invoke

.template T
    x db ?
    y db ?
   .ends

foo proto :byte {}
bar proto {}
baz proto {}

.code

main proc

    .if foo([bar()].T.x)    ; foo([al].T.x)
        nop
    .endif
    addss baz(),xmm1        ; addss rax,xmm1
    ret
    endp
    end
