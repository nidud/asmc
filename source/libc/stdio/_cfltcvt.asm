; _TCFLTCVT_TAB.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include stdlib.inc
include fltintrn.inc

    .data
     _cfltcvt_tab PF0 _fptrap

    .code

_fptrap proc

    mov eax,_fltused
    _write( 1, "floating point not loaded\n", 26 )
    _exit( 1 )

_fptrap endp

    end
