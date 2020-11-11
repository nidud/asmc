
; v2.31.24 proto {

    .x64
    .model flat, fastcall

    option win64:auto
    option casemap:none

foo proto :ptr, :abs, :real4 {

    mov     rax,_1      ; cx
    mov     al,_2+2     ; 2
    movss   xmm0,_3     ; xmm2
    }

real4::add proto :real4 {

    addss   _1,_2
    }

real4::real8 proto {

    cvtss2sd _1,_1
    movq    rax,_1
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
