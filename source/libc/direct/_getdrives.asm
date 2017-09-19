include winbase.inc

    .code

_getdrives proc
    GetLogicalDrives()
    ret
_getdrives endp

    END
