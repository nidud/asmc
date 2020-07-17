
    ; Tokenize quote failed: <"\"" )> -- <""\"")">

    .x64
    .model flat, fastcall
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
