
; v2.30 - .NEW directive

    .x64
    .model flat, fastcall
    .code

.class T :word
.ends
.class M
.ends

undef M_M
M_M macro val
    nop
    endm

    .code

T::T proc x:word
    mov rax,this
    mov ax,x
    ret
T::T endp

main proc

    .new T(0)
    .new M()
    .new p:ptr T(2)
    ret

main endp

    end
