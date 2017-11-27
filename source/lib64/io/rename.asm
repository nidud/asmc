include io.inc
include winbase.inc

.code

option win64:rsp nosave

rename proc Oldname:LPSTR, Newname:LPSTR

    .if MoveFile(rcx, rdx)
        xor rax,rax
    .else
        osmaperr()
    .endif
    ret

rename endp

    end
