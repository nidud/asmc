
; extend r/m32 param to m64

.486
.model flat, c
.code

foo proc q:qword, p:qword
    ret
foo endp

bar proc d:sdword, p:ptr

    invoke foo, d, p
    invoke foo, eax, eax
    invoke foo, sdword ptr eax, sdword ptr eax
    ret

bar endp

end
