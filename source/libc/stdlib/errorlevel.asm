; ERRORLEVEL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    public errorlevel  ; Exit Code from GetExitCodeProcess

    .data
     errorlevel int_t 0

    end
