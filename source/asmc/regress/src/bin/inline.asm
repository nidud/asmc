
; v2.31.08 proto and macros

    .x64
    .model flat, fastcall

    option win64:auto
    option casemap:none

foo proto :word, :byte, :real4

foo macro  a, b, c ; cx, dl, xmm2
    mov ax,a
    mov al,b
    exitm<movss xmm0,c>
    endm

    .code

main proc

    foo(1,2,3.0)
    ret

main endp

    end
