; v2.37.71 - .pragma aux() on register pair

    .x64
    .model flat, asmcall

    ; default(ax, dx, cx)

    aux0    proto :ptr, :ptr, :ptr
    aux0a   proto :oword, :ptr
    aux0b   proto :ptr, :oword

    .pragma aux(si, di, bx)

    aux1    proto :ptr, :ptr, :ptr
    aux1a   proto :oword, :ptr
    aux1b   proto :ptr, :oword

    .pragma aux(r8, r9, r10)

    aux2    proto :ptr, :ptr, :ptr
    aux2a   proto :oword, :ptr
    aux2b   proto :ptr, :oword

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
aux0a proc q:oword, p:ptr
    ret
    endp
aux0b proc p:ptr, q:oword
    ret
    endp
aux1 proc a:ptr, b:ptr, c:ptr
    ret
    endp
aux1a proc q:oword, p:ptr
    ret
    endp
aux1b proc p:ptr, q:oword
    ret
    endp
aux2 proc a:ptr, b:ptr, c:ptr
    ret
    endp
aux2a proc q:oword, p:ptr
    ret
    endp
aux2b proc p:ptr, q:oword
    ret
    endp

    end
