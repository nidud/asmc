; _TUNLINK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include tchar.inc

.code

_tunlink proc path:tstring_t

    ldr rcx,path

    _tremove(rcx)
    ret

_tunlink endp

    end
