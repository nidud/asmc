; AUTO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Asmc detect use of floats and main(params) with option -MT
;
include stdio.inc
include tchar.inc

.code

; This has no effect in Linux..
ifdef USEARGV
_tmain proc argc:int_t, argv:array_t
else
_tmain proc
endif

ifdef USEFLT
    _tprintf("Float value: %f\n", 2.5)
else
    _tprintf("No floats used\n")
endif
   .return( 0 )

_tmain endp

    end _tstart
