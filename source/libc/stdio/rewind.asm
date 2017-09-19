include io.inc
include stdio.inc
include winbase.inc

    .code

rewind proc fp:LPFILE

    fflush(fp)
    mov ecx,fp
    mov eax,[ecx]._iobuf._flag
    and eax,not (_IOERR or _IOEOF)
    .if eax & _IORW
        and eax,not (_IOREAD or _IOWRT)
    .endif
    mov [ecx]._iobuf._flag,eax
    mov eax,[ecx]._iobuf._file
    and _osfile[eax],not FH_EOF
    mov eax,_osfhnd[eax*4]
    SetFilePointer(eax, 0, 0, SEEK_SET)
    ret

rewind endp

    END
