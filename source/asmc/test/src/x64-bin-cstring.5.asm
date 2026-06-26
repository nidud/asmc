
    ; 2.34.42 - Tokenize quote failed on text macro

.code

option casemap:none, win64:auto

foo proc a:ptr sbyte, b:ptr sbyte
    ret
    endp

define _tfoo <foo>

main proc
    _tfoo( "\"", "\"" ) ; <foo>, <(>, <">, <,>, <">, <)>, <>
    ret
    endp

    end
