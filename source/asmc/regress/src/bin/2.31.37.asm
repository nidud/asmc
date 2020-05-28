
    ; template: recursive type

    .x64
    .model flat, fastcall

    option casemap:none
    option win64:auto

    ostream typedef ptr

.template ostream

    .operator << :ptr {}

    .ends
    cout equ <ostream::>

    .code

main proc

    cout << "string" << "string2" << "string3"
    ret

main endp

    end
