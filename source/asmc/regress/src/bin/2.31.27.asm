
    .x64
    .model flat, fastcall

    option casemap:none
    option win64:auto

.class C

    C proc :dword

    .ends

    .data
    x C (4) dup(<>)

    .code

foo proc a:ptr, b:ptr, c:ptr, d:ptr, e:ptr, f:real4

    ret

foo endp

main proc

  local r:real4

    mov r,200.0

    C(0)

    foo(0,0,0,0,[rsp+8],xmm3)
    ret

main endp

C::C proc val:dword
    ret
C::C endp

    end
