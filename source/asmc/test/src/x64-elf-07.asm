;
; v2.31 - stack param and xmm
;

    .code

    option win64:auto

    F2 typedef real2
    F4 typedef real4
    F8 typedef real8

foo proto :F8,:F8,:F8,:F8,:F8,:F8,:F8,:F8, :F4
bar proto :F8,:F8,:F8,:F8,:F8,:F8,:F8,:F8, :F8,:F2

main proc

    foo(xmm0,xmm1,xmm2,xmm3,xmm4,xmm5,xmm6,xmm7, xmm20)
    bar(xmm0,xmm1,xmm2,xmm3,xmm4,xmm5,xmm6,xmm7, xmm8,xmm9)

    ret

main endp

    end
