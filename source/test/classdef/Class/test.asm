include class.inc

    .code

main proc

  .new p:ptr Class( "String" )

    p.Print()
    p.Release()

  .new s:Class( "String2" )

    s.Print()
    ret

main endp

    end
