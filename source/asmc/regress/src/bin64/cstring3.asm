
    ; 2.31.48 - Tokenize quote failed: <"\"" )> -- <""\"")">

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif
    .code

    option casemap:none, win64:auto

foo proc a:ptr sbyte, b:ptr sbyte
    ret
foo endp

main proc

    foo( "\"", "\"" ) ; <foo>, <(>, <">, <,>, <">, <)>, <>
    ret

main endp

    end
