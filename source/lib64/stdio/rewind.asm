include io.inc
include stdio.inc
include winbase.inc

    .code

rewind proc fp:LPFILE

    fflush(rcx)
    mov rcx,fp
    mov eax,[rcx]._iobuf._flag
    and eax,not (_IOERR or _IOEOF)
    .if eax & _IORW
	and eax,not (_IOREAD or _IOWRT)
    .endif
    mov [rcx]._iobuf._flag,eax
    mov eax,[rcx]._iobuf._file
    lea rcx,_osfile
    and byte ptr [rcx+rax],not FH_EOF
    lea rcx,_osfhnd
    mov rcx,[rcx+rax*8]
    SetFilePointer(rcx, 0, 0, SEEK_SET)
    ret

rewind endp

    end
