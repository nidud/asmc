
    ; 2.31.40 - expansion of strings in second pass

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif
    .code

foo proc string:ptr sbyte
    ret
foo endp

.template bar
    .inline pass2 { foo("error") }
    .ends

    .code

main proc

  local b:bar

    b.pass2()
    ret

main endp

    end
