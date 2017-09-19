include errno.inc

errnomsg proto :LPSTR, :LPSTR, :LPSTR

    .code

erdelete proc file:LPSTR
    errnomsg("Error delete", "Can't delete the file:\n%s\n\n%s", file)
    ret ; return -1
erdelete endp

    end
