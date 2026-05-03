
    ; constructor

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif

    option casemap:none
    option win64:auto

.class C

    C proc :dword

    .ends

    .data
    x C (4) dup(<>)

    .code

main proc

    C(0)
    ret

main endp

C::C proc val:dword
    ret
C::C endp

    end
