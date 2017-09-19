include crtl.inc
include io.inc
include winbase.inc

    .code

setfattr proc lpFilename:LPTSTR, Attributes:UINT

    .if !SetFileAttributes(lpFilename, Attributes)

        osmaperr()
    .else

        xor eax,eax
        mov byte ptr _diskflag,2
    .endif
    ret
setfattr endp

    END
