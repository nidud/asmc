include class.inc

    .code

main proc

  local p:LPCLASS, s:Class

    .if Class::Class( NULL, "String" )

        mov p,rax

        p.Print()
        p.Release()
    .endif

    .if Class::Class( &s, "String2" )

        s.Print()
    .endif
    ret

main endp

    end
