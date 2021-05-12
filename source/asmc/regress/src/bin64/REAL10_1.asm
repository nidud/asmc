
    ; 2.32.33 - REAL10

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif
    .code

    option win64:3

foo proc r1:real10, r2:real10, r3:real10

    lea rax,r1
    lea rax,r2
    lea rax,r3
    ret

foo endp

bar proc a:real10

  local r:real10

    foo(a, r, 3.0)
    ret

bar endp

    end
