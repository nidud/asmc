include io.inc
include time.inc
include winbase.inc
include dzlib.inc

    .code

setftime_access proc uses edx ecx h:SINT, t:SIZE_T

  local FileTime:FILETIME

    .if getosfhnd(h) != -1

        mov edx,eax
        .if SetFileTime(edx, 0, __TimeToFT(t, addr FileTime), 0)

            xor eax,eax
            mov byte ptr _diskflag,2
        .else
            osmaperr()
        .endif
    .endif
    ret

setftime_access endp

    END
