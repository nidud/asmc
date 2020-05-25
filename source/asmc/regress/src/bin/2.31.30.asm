
    ; : public template

    .x64
    .model flat, fastcall

    option casemap:none
    option win64:auto

.template template

    atom        db ?

    template    proc :ptr
    Release     proc

    .ends

.class class : public template

    class       proc :ptr

    .ends

    .code

main proc

  local T:template
  local C:class

    mov C.lpVtbl,rax    ; lpVtbl added to class
    mov C.atom,al

    movq    xmm0,3FF0000000000000r
    movsd   xmm0,1.0
    addsd   xmm0,1.0
    subsd   xmm0,1.0
    mulsd   xmm0,1.0
    divsd   xmm0,1.0
    comisd  xmm0,1.0
    ucomisd xmm0,4.0 / 2.0 - 1.0

    movd    xmm0,3F800000r
    movss   xmm0,1.0
    addss   xmm0,1.0
    subss   xmm0,1.0
    mulss   xmm0,1.0
    divss   xmm0,1.0
    comiss  xmm0,1.0
    ucomiss xmm0,4.0 / 2.0 - 1.0

    ret

main endp

    end
