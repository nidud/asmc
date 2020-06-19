
    ; template: recursive type

    .x64
    .model flat, fastcall

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
