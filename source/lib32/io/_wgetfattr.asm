include io.inc
include direct.inc
include winbase.inc

.code

_wgetfattr proc uses ecx edx lpFilename:LPWSTR

    .if GetFileAttributesW(lpFilename) == -1

        osmaperr()
    .endif
    ret

_wgetfattr endp

    end

