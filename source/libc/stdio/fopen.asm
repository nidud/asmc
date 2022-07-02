; FOPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include share.inc

    .code

fopen proc fname:LPSTR, mode:LPSTR

    .if _getst()

        _openfile( fname, mode, SH_DENYNO, rax )
    .endif
    ret

fopen endp

    end
