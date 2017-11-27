include io.inc
include winbase.inc

.code

_wremove proc file:LPWSTR

    .if DeleteFileW(rcx)

        xor eax,eax
    .else
        osmaperr()
    .endif
    ret

_wremove endp

    end
