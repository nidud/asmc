
include quadmath.inc

compare macro op, x, y, z
    local r
    .data
ifnb <z>
    r real16 z
    .code
    op(x, y)
else
    r real16 y
    .code
    op(x)
endif
    movq    rcx,xmm0
    movhlps xmm0,xmm0
    movq    rax,xmm0
    mov     rbx,qword ptr r[8]
    mov     rdx,qword ptr r
    rol     rcx,8
    rol     rdx,8
    .assert( rax == rbx && cl == dl )
    exitm<>
    endm

.code

main proc
    compare(acosqf, 0.0, 1.570796326794896619)
    compare(acosqf, 0.5, 1.047197551196597721)
    compare(atanqf, 0.0, 0.0)
    compare(atanqf, 1.5, 0.9827937232473290680)
    compare(atan2qf, 0.0, 0.0, 0.0)
    compare(atan2qf, 0.5, 1.5, 0.3217505543966421934)
    compare(ceilqf, 0.0, 0.0)
    compare(ceilqf, 2.5, 3.0)
    compare(cosqf, 0.0, 1.0)
    compare(cosqf, 10.0, -0.8390715290764524523)
    compare(expqf, 0.0, 1.0)
    compare(expqf, 1.5, 4.481689070338065406)
    compare(floorqf, 0.0, 0.0)
    compare(floorqf, 2.57, 2.0)
    compare(fmodqf, 1.0, 1.0, 0.0)
    compare(fmodqf, 1.5, 1.2, 0.3)
    compare(logqf, 1.5, 0.4054651081081643820)
    compare(log10qf, 1.5, 0.1760912590556812421)
    compare(sinqf, 0.0, 0.0)
    compare(sinqf, 0.5, 0.4794255386042030003)
    compare(sqrtqf, 0.0, 0.0)
    compare(sqrtqf, 1.0, 1.0)
    compare(sqrtqf, 2.0, 1.414213562373095148)
    compare(tanqf, 0.0, 0.0)
    compare(tanqf, 1.5, 14.10141994717171939)
    xor eax,eax
    ret

main endp

    end
