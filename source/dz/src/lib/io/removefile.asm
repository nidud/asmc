include io.inc
include dzlib.inc

    .code

removefile proc file:LPSTR
    setfattr(file, 0)
    remove(file)
    ret
removefile endp

    END
