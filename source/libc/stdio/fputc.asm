include stdio.inc

    .code

fputc proc char:SINT, fp:LPFILE

    mov eax,char
    mov ecx,fp
    dec [ecx]._iobuf._cnt
    .ifl
        _flsbuf(eax, ecx)
    .else
        mov edx,[ecx]._iobuf._ptr
        add [ecx]._iobuf._ptr,1
        mov [edx],al
    .endif
    ret

fputc endp

    END
