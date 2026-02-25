; _TFGETCHAR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include tchar.inc

.code

_fgettchar proc
    .return(_gettc(stdin))
    endp

_gettchar proc
    .return _fgettchar()
    endp

    end
