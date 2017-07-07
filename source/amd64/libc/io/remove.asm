include io.inc
include winbase.inc

    .code

    option win64:rsp nosave

remove proc file:LPSTR
    .if DeleteFileA(rcx)
        xor rax,rax
    .else
        osmaperr()
    .endif
    ret
remove endp

    END
