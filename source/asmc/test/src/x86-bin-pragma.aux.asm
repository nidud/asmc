; v2.37.71 - .pragma aux() on register pair

    .486
    .model flat, asmcall

    ; default(ax, dx, cx)

    aux0    proto :ptr, :ptr, :ptr
    aux0a   proto :qword, :ptr
    aux0b   proto :ptr, :qword

    .pragma aux(si, di, bx)

    aux1    proto :ptr, :ptr, :ptr
    aux1a   proto :qword, :ptr
    aux1b   proto :ptr, :qword

    .pragma aux(cx, bx, ax)

    aux2    proto :ptr, :ptr, :ptr
    aux2a   proto :qword, :ptr
    aux2b   proto :ptr, :qword

    .code

main proc

    aux0(1, 2, 3)
    aux0a(1, 2)
    aux0b(1, 2)
    aux1(1, 2, 3)
    aux1a(1, 2)
    aux1b(1, 2)
    aux2(1, 2, 3)
    aux2a(1, 2)
    aux2b(1, 2)
    aux0(1, 2, 3)
    ret
    endp

aux0 proc a:ptr, b:ptr, c:ptr
    ret
    endp
aux0a proc q:qword, p:ptr
    ret
    endp
aux0b proc p:ptr, q:qword
    ret
    endp
aux1 proc a:ptr, b:ptr, c:ptr
    ret
    endp
aux1a proc q:qword, p:ptr
    ret
    endp
aux1b proc p:ptr, q:qword
    ret
    endp
aux2 proc a:ptr, b:ptr, c:ptr
    ret
    endp
aux2a proc q:qword, p:ptr
    ret
    endp
aux2b proc p:ptr, q:qword
    ret
    endp

    end
