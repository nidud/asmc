
; v2.31.24 proto {

    .x64
    .model flat, fastcall

    option win64:auto
    option casemap:none

foo proto :ptr, :abs, :real4 {

    mov     rax,this    ; cx
    mov     al,_1+2     ; 2
    movss   xmm0,_2     ; xmm2
    exitm   <>
    }

real4::add proto :real4 {

    addss   this,_1
    retm    <this>
    }

real4::real8 proto {

    cvtss2sd this,this
    movq    rax,this
    retm    <this>
    }

    .code

main proc

  local float:real4
  local double:real8

    movss float,  foo( &[rdx], 2, 3.0 )
    movsd double, real4::real8( real4::add( 1.0, 2.0 ) )
    ret

main endp

    end
