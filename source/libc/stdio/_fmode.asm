; _FMODE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include fcntl.inc

public _fmode

    .data
     _fmode dd O_TEXT

    end
