; MANIFEST.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include tchar.inc

.code

_tmain proc argc:int_t, argv:array_t

    _tprintf("The MANIFEST project\n")
   .return(0)

_tmain endp

    end _tstart
