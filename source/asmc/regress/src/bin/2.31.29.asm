
    .686
    .model flat, c
    .code

foo proc p:ptr, v:vararg
    ret
foo endp

main proc

  local f:real16

    foo(0, f)
    ret

main endp

    end
