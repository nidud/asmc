; _ldtoqf() - long double to Quadruple float
;
include intn.inc

.code
option win64:rsp nosave noauto

_ldtoqf proc p:ptr, ld:ptr

    mov rax,rcx
    mov cx,[rdx+8]
    mov [rax+14],cx
    mov rcx,[rdx]
    shl rcx,1
    xor rdx,rdx
    mov [rax],rdx
    mov [rax+6],rcx
    ret

_ldtoqf endp

    end
