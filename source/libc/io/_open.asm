; _OPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include share.inc

    .code

_open proc path:LPSTR, oflag:SINT, args:VARARG
ifdef __UNIX__
    mov ecx,[rax+4]
    _sopen( path, oflag, SH_DENYNO, ecx )
else
    _sopen( path, oflag, SH_DENYNO, args )
endif
    ret

_open endp

    end
