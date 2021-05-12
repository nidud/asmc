
; v2.30 - .NEW directive

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif
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
