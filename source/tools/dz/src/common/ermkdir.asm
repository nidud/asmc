include errno.inc

PUBLIC  cp_mkdir
errnomsg proto :LPSTR, :LPSTR, :LPSTR

    .data
    cp_mkdir  db "Make directory",0

    .code

ermkdir proc directory:LPSTR
    errnomsg(addr cp_mkdir, "Can't create the directory:\n%s\n\n%s", directory)
    ret
ermkdir endp

    END
