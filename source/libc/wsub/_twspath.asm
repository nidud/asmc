; _TWSPATH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include wsub.inc
include string.inc
include direct.inc
include tchar.inc

.code

_wspath proc wp:PWSUB, path:LPTSTR

    ldr rcx,wp
    ldr rdx,path

    .if ( rdx )
        _tcscpy([rcx].WSUB.path, rdx)
    .else
        _tgetcwd([rcx].WSUB.path, WMAXPATH)
    .endif
    ret

_wspath endp

    end
