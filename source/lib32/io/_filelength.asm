include io.inc
include errno.inc
include winbase.inc

    .code

filelength proc handle:SINT
filelength endp

_filelength proc handle:SINT

local lpFileSize:qword

    mov eax,handle
    mov edx,_osfhnd[eax*4]

    .if !GetFileSizeEx(edx, &lpFileSize)

        mov edx,osmaperr()
    .else
        mov edx,dword ptr lpFileSize[4]
        mov eax,dword ptr lpFileSize
    .endif
    ret

_filelength endp

    END
