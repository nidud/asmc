
    ; template: vararg
    ; vector(16)
    ; typeof(addr p)

    .x64
    .model flat, fastcall

    option casemap:none
    option win64:auto

.template Pen

    atom byte ?

    Pen proc :vararg
    Pen_Pen macro this, _1, _2:=<1.0>, _3:=<0>
        ifb <_1>
            this.Pen0()
        elseif typeof(_1) eq 2
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

    mov eax,typeof(a)       ; 1
    mov eax,typeof(addr a)  ; 8

    ; assign vector(16)

    movaps xmm0,{ 1.0 }
    movapd xmm0,{ 1.0, 2.0 }
    movaps xmm0,{ 1.0, 2.0, 3.0, 4.0 }
    movaps xmm0,{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 }

    movdqa xmm0,{ 1 }
    movapd xmm0,{ 1, 2 }
    movups xmm0,{ 1, 2, 3, 4 }
    movaps xmm0,{ 1, 2, 3, 4, 5, 6, 7, 8 }
    movupd xmm0,{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }

    ; use vector(16)

    divpd xmm0,{ 1.0 }
    addpd xmm0,{ 1.0, 2.0 }
    xorpd xmm0,{ 1.0, 2.0, 3.0, 4.0 }
    mulpd xmm0,{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 }

    divps xmm0,{ 1 }
    addps xmm0,{ 1, 2 }
    xorps xmm0,{ 1, 2, 3, 4 }
    mulps xmm0,{ 1, 2, 3, 4, 5, 6, 7, 8 }
    subps xmm0,{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }

    ; return vector(16)

    .return { 1.0 }
    .return { 1.0, 2.0 }
    .return { 1.0, 2.0, 3.0, 4.0 }
    .return { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 }

    .return { 1 }
    .return { 1, 2 }
    .return { 1, 2, 3, 4 }
    .return { 1, 2, 3, 4, 5, 6, 7, 8 }
    .return { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }

    ret

main endp

    end
