
    ; 2.34.42 - Tokenize quote failed on text macro

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif
    .code

    option casemap:none, win64:auto

foo proc a:ptr sbyte, b:ptr sbyte
    ret
foo endp

define _tfoo <foo>

main proc

    _tfoo( "\"", "\"" ) ; <foo>, <(>, <">, <,>, <">, <)>, <>
    ret

main endp

    end
