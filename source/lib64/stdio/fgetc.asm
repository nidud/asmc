include stdio.inc

    .code

    option win64:rsp nosave noauto

fgetc proc fp:LPFILE
    dec [rcx]._iobuf._cnt
    .ifl
        _filbuf(rcx)
    .else
        inc [rcx]._iobuf._ptr
        mov rax,[rcx]._iobuf._ptr
        movzx eax,byte ptr [rax-1]
    .endif
    ret
fgetc endp

    END
