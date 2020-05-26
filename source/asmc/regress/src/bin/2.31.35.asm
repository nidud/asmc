
    ; WATCALL

    .486
    .model flat, c
    .code

wc proc watcall a:qword, b:qword

    ret

wc endp

fc proc fastcall a:qword, b:qword

    wc(a, b)
    ret

fc endp

main proc

    wc(1, 2)
    fc(1, 2)
    ret

main endp

    end
