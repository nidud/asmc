; _BUFIN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

PUBLIC	_bufin

    .data
    _bufin db _INTIOBUF dup(0)

    end
