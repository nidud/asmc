; _GETCWD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include direct.inc

    .code

    option win64:nosave

_getcwd proc buffer:LPSTR, maxlen:SINT

    _getdcwd(0, rcx, edx)
    ret

_getcwd endp

    end
