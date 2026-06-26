
    ; 2.31.40 - expansion of strings in second pass

    .code

foo proc string:ptr sbyte
    ret
    endp

.template bar
    .inline pass2 { foo("error") }
    .ends

    .code

main proc

  local b:bar

    b.pass2()
    ret
    endp

    end
