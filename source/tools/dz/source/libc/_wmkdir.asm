; _WMKDIR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include direct.inc
include errno.inc
include winbase.inc

externdef _diskflag:DWORD

    .code

_wmkdir proc directory:LPWSTR

    .if CreateDirectoryW(directory, 0)

        xor eax,eax
        mov _diskflag,1

    .else
        osmaperr()
    .endif
    ret

_wmkdir endp

    END
