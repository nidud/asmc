; _GETCWD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include direct.inc

    .code

    option win64:nosave

_getcwd proc buffer:LPSTR, maxlen:SINT

    mov r8d,edx
    mov rdx,rcx
    _getdcwd(0, rdx, r8d)
    ret

_getcwd endp

    end
