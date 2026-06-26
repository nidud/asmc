
; 2.31.41 - "\0" --> db 0, 0

.code

foo proc string:ptr sbyte
    ret
    endp

main proc
    foo("\0")
    ret
    endp

    end
