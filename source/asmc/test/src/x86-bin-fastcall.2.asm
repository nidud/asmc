
    ; v2.31.35: fastcall return error

    .486
    .model flat, c
    .code

wc proc watcall a:qword, b:qword

    ret

wc endp

fc proc fastcall a:qword, b:qword

    wc(a, b)
    ret ; ret 16

fc endp

main proc

    wc(1, 2) ; regs only
    fc(1, 2) ; stack only
    ret

main endp

    end
