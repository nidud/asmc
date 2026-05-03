
    ; 2.31.41 - "\0" --> db 0, 0

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif
    .code

foo proc string:ptr sbyte
    ret
foo endp

main proc

    foo("\0")
    ret

main endp

    end
