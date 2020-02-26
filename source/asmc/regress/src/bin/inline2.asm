
; v2.31.18 :ABS

    .x64
    .model flat, fastcall

    option win64:auto
    option casemap:none

foo proto :ptr, :abs, :real4

foo macro  a, b, c ; cx, dl, xmm2
    mov rax,a
    mov al,b+2
    exitm<movss xmm0,c>
    endm

    .code

main proc

    foo(&[rdx],2,3.0)
    ret

main endp

    end
