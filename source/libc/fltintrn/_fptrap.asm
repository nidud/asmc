; _FPTRAP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include stdlib.inc
include fltintrn.inc

    .code

_fptrap proc

    _write( 1, "floating point not loaded\n", 26 )
    _exit( 1 )

_fptrap endp

    end
