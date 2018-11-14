include math.inc
include intrin.inc

comp64 macro r, p, args:vararg
  local x
    .data
    x dq r
    .code
    p(args)
    movq rax,xmm0
    mov  rbx,x
    exitm<.assert(rax == rbx)>
    endm

comp32 macro r, p, args:vararg
  local x
    .data
    x dq r
    .code
    p(args)
    movq rax,xmm0
    shr  rax,32
    mov  ebx,dword ptr x[4]
    exitm<.assert(eax == ebx)>
    endm

    .code

main proc

    comp64(1.1493775572794240, cosh, -0.54)
    comp32(34.466919, exp, 3.54)
    comp64(2.0, floor, 2.57)
    comp32(0.3, fmod, 1.5, 1.2)
    comp64(2.0, sqrt, 4.0)
    comp32(3.240370, sqrt, 10.5)
    comp64(12.0, round, 12.4)
    comp64(13.0, round, 12.5)
    comp32(0.4636476090008061, atan2, 1.0, 2.0)
    comp64(3.0, ceil, 2.5)
    comp32(0.46211715726001, tanh, 0.5)

    xor eax,eax
    ret

main endp

    end
