
    ; 2.31.32
    ; template: vararg

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif
    option casemap:none
    option win64:auto

.template Pen

    atom byte ?

    Pen proc :vararg
    Pen_Pen macro this, _1, _2:=<1.0>, _3:=<0>
        ifb <_1>
            this.Pen0()
        elseif TYPEOF(_1) eq 2
            this.Pen1(_1, _2, _3, rcx)
        else
            this.Pen2(_1, _2)
        endif
        lea rax,this
        exitm<>
        endm

    .inline Pen0 {
        mov dl,0
        }
    .inline Pen1 :word, :real4, :word, :ptr {
        mov dl,1
        }
    .inline Pen2 :ptr, :real8 {
        mov dl,2
        }

    .ends

    .code

main proc

    ; only non-vararg args loded by INVOKE: lea rcx,a
    ; The macro is served with the actual arg-list

    .new a:Pen()            ; Pen_Pen(a)
    .new b:Pen([rbx], 2.0)  ; Pen_Pen(b, [rbx], 2.0)
    .new c:Pen(ax)          ; Pen_Pen(c, ax)
    ret

main endp

    end
