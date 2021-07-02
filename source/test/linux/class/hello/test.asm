include class.inc

    .code

main proc

  local p:LPCLASS

    Class::Class(&p, "Hello Class!" )

    p.Print()
    p.Release()
    ret

main endp

    end
