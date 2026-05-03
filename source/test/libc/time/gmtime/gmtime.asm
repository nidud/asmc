; GMTIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include stdio.inc
include time.inc
include tchar.inc

.code

_tmain proc

   .new newtime:ptr tm
   .new ltime:time_t

    _time( &ltime )
    mov newtime,gmtime( &ltime )
    _tprintf( "Coordinated universal time is %s\n", asctime(newtime) )

   .return( 0 )

_tmain endp

    end _tstart
