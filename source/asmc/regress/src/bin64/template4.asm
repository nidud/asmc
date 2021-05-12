
    ; 2.31.37 - template: recursive type

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif
    option casemap:none, win64:auto

    ostream typedef ptr
    cout    equ <ostream::>

.template ostream
    .operator << :ptr {}
    .ends

    .code

main proc

    cout << "string" << "string2" << "string3"
    ret

main endp

    end
