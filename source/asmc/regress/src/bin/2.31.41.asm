
    ; "\0" --> db 0, 0

    .x64
    .model flat, fastcall
    .code

foo proc string:ptr sbyte
    ret
foo endp

main proc

    foo("\0")
    ret

main endp

    end
