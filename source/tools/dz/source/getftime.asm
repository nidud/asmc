include io.inc
include time.inc
include winbase.inc

    .code

getftime proc uses ecx edx handle:SINT

  local FileTime:FILETIME

    .if getosfhnd(handle) != -1

        mov edx,eax
        .if !GetFileTime(edx, 0, 0, addr FileTime)

            osmaperr()
        .else
            __FTToTime(addr FileTime)
        .endif
    .endif
    ret

getftime endp

getftime_access proc uses ecx edx handle:SINT

  local FileTime:FILETIME

    .if getosfhnd(handle) != -1

        mov edx,eax
        .if !GetFileTime(edx, 0, addr FileTime, 0)

            osmaperr()
        .else
            __FTToTime(addr FileTime)
        .endif
    .endif
    ret

getftime_access endp

getftime_create PROC USES ecx edx handle:SINT

  local FileTime:FILETIME

    .if getosfhnd( handle ) != -1

        mov edx,eax
        .if !GetFileTime( edx, addr FileTime, 0, 0 )

            osmaperr()
        .else
            __FTToTime( addr FileTime )
        .endif
    .endif
    ret

getftime_create ENDP

    END
