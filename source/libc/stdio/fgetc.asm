include stdio.inc

    .code

fgetc proc fp:LPFILE

    mov eax,fp
    dec [eax]._iobuf._cnt
    .ifl
        _filbuf(eax)
    .else
        add [eax]._iobuf._ptr,1
        mov eax,[eax]._iobuf._ptr
        movzx eax,byte ptr [eax-1]
    .endif
    ret

fgetc endp

    END
