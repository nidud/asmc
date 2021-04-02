
    .x64
    .model flat, fastcall

    option casemap:none
    option win64:auto

S1  STRUC
m1  dw ?
m2  dd ?
S1  ENDS

    .code

foo proc a:ptr sbyte, b:dword
    ret
foo endp

main proc

    .new string:ptr sbyte = "string"
    .new s:S1 = {
        foo( "string", 1 ),
        foo( string, 2 )
        }

    ret

main endp

    end
