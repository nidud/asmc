
    ; 2.31.27

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif

    option casemap:none
    option win64:auto

    .code

foo proc a:ptr, b:ptr, c:ptr, d:ptr, e:ptr, f:real4

    ret

foo endp

main proc

  local r:real4

    mov r,200.0

    foo(0,0,0,0,[rsp+8],xmm3)
    ret

main endp

    end
