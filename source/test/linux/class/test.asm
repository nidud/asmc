include class.inc

    .code

main proc

   .new p:ptr Class("Hello Class!")

    p.Print()
    p.Release()
    ret

main endp

    end
