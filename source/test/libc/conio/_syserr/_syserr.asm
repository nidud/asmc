; _SYSERR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include errno.inc
include tchar.inc

.code

_tmain proc

    _set_errno(22)
    _eropen(__FILE__)
    _syserr("Error open file", "Can't open the file:\n%s", __FILE__)
   .return(0)

_tmain endp

    end _tstart
