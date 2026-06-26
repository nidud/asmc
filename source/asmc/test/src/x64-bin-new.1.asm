
; v2.30 - .NEW directive

.code

.class T
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
    endp

main proc
   .new T(0)
   .new M()
   .new p:ptr T(2)
    ret
    endp

    end
