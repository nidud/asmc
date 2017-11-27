include io.inc
include errno.inc
include winbase.inc

.code

oswrite proc h:SINT, b:PVOID, z:SIZE_T
local NumberOfBytesWritten:dword
    mov eax,h
    mov edx,_osfhnd[eax*4]
    .if WriteFile(edx, b, z, &NumberOfBytesWritten, 0)
        mov eax,NumberOfBytesWritten
        .if eax != z
            mov errno,ERROR_DISK_FULL
            xor eax,eax
        .endif
    .else
        osmaperr()
        xor eax,eax
    .endif
    ret
oswrite endp

    end
