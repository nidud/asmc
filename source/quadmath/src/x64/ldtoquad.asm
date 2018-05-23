;
; ldtoquad() - long double to Quadruple float
;
include quadmath.inc

    .code

    option win64:rsp nosave noauto

ldtoquad proc p:ptr, ld:ptr
ifdef _LINUX
    mov rax,rdi
    mov rdx,rsi
else
    mov rax,rcx
endif
    mov cx,[rdx+8]
    mov [rax+14],cx
    mov rcx,[rdx]
    shl rcx,1
    xor rdx,rdx
    mov [rax],rdx
    mov [rax+6],rcx
    ret
ldtoquad endp

    end
