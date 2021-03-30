
    .x64
    .model flat, fastcall

    option casemap:none
    option win64:auto

POINT   struct
x       dd ?
y       dd ?
POINT   ends

.code

main proc

    .new p[2]:POINT = { { 1, 2 }, { 3, 4 } }

    ret

main endp

    end
