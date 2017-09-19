include io.inc
include winbase.inc

    .code

_wrename proc Oldname:LPWSTR, Newname:LPWSTR

    .if MoveFileW(Oldname, Newname)

        xor eax,eax
    .else
        osmaperr()
    .endif
    ret

_wrename endp

    end
