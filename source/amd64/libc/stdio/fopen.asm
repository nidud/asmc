include stdio.inc
include share.inc

    .code

    option win64:rsp nosave

fopen proc fname:LPSTR, mode:LPSTR

    .if _getst()

        _openfile(rcx, rdx, SH_DENYNO, rax)
    .endif
    ret

fopen endp

    END
