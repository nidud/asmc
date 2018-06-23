include quadmath.inc

.code

main proc

  local x:REAL16
  local y:REAL16
  local exponent:dword
  local eptr:LPSTR

comprr macro a, b
    mov rax,qword ptr a
    mov rdx,qword ptr a+8
    mov rbx,qword ptr b
    mov rcx,qword ptr b+8
    exitm<.assert(rax == rbx && rdx == rcx)>
    endm

compval macro a, val
    local b
    .data
    b real16 val
    .code
    exitm<comprr(a, b)>
    endm

compare macro a, val, p, e
    compval(a, val)
    mov rdx,p
    mov al,[rdx]
    exitm<.assert(al == e)>
    endm

    atoquad(&x, ".", &eptr )
    compare(x, 0.0, eptr, '.')
    atoquad(&x, "-1.0e-0a", &eptr )
    compare(x, -1.0, eptr, 'a')
    atoquad(&x, "-1e-0a", &eptr )
    compare(x, -1.0, eptr, 'a')
    atoquad(&x, "123456789.0", &eptr )
    compare(x, 123456789.0, eptr, 0)

if 0 ; hex removed..
    atoquad(&x, "0x1g", &eptr )
    compare(x, 1.0, eptr, 'g')
    atoquad(&x, "0x2", &eptr )
    compval(x, 2.0)
    atoquad(&x, "0x4", &eptr )
    compval(x, 4.0)
    atoquad(&x, "0x8", &eptr )
    compval(x, 8.0)
endif
    xor eax,eax
    ret

main endp

    end
