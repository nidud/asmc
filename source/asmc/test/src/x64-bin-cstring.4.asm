
    ; 2.31.48 - Tokenize quote failed: <"\"" )> -- <""\"")">

.code

option casemap:none, win64:auto

foo proc a:ptr sbyte, b:ptr sbyte
    ret
    endp

main proc
    foo( "\"", "\"" ) ; <foo>, <(>, <">, <,>, <">, <)>, <>
    ret
    endp

    end
