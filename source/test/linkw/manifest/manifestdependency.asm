; MANIFESTDEPENDENCY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include tchar.inc

.pragma comment(linker,
    "/manifestdependency:\""
    "type='win32' "
    "name='Microsoft.Windows.Common-Controls' "
    "version='6.0.0.0' "
    "processorArchitecture='*' "
    "publicKeyToken='6595b64144ccf1df' "
    "language='*'"
    "\""
    )

.code

_tmain proc argc:int_t, argv:array_t

    _tprintf("The MANIFESTDEPENDENCY project\n")
   .return(0)

_tmain endp

    end _tstart
