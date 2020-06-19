
    ; expansion of strings in second pass

    .x64
    .model flat, fastcall
    .code

foo proc string:ptr sbyte
    ret
foo endp

.template bar
    .operator pass2 { foo("error") }
    .ends

    .code

main proc

  local b:bar

    b.pass2()
    ret

main endp

    end
