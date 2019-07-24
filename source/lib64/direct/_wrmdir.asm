; _WRMDIR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include direct.inc
include errno.inc
include winbase.inc

    .code

_wrmdir proc frame directory:LPWSTR

    .if RemoveDirectoryW(rcx)
        xor eax,eax
    .else
        _dosmaperr(GetLastError())
    .endif
    ret

_wrmdir endp

    END
