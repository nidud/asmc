include consx.inc

    .code

mousewait proc x, y, l
    mov edx,x
    add edx,l
    .while  mousep()
        .break .if mousey() != y
        .break .if mousex() < x
        .break .if eax > edx
    .endw
    ret
mousewait endp

    END
