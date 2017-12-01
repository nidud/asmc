include stdio.inc

    .code

    option win64:rsp nosave noauto

feof proc stream:LPFILE
    mov eax,[rcx]._iobuf._flag
    and rax,_IOEOF
    ret
feof endp

    END
