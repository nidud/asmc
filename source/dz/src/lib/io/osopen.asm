include io.inc
include winbase.inc

    .code

osopen proc file:LPSTR, attrib, mode, action
    mov ecx,mode
    .if ecx != M_RDONLY
        mov byte ptr _diskflag,1
    .endif
    xor eax,eax
    .if ecx == M_RDONLY
        mov eax,FILE_SHARE_READ
    .endif
    _osopenA(file, ecx, eax, 0, action, attrib)
    ret
osopen endp

    END
