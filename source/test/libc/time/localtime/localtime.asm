; LOCALTIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include time.inc
include tchar.inc

.code

_tmain proc argc:int_t, argv:array_t

   .new ltime:time_t = time(0)

    mov rbx,localtime(&ltime)
    _tprintf(
        " tm_sec:   %d\n"
        " tm_min:   %d\n"
        " tm_hour:  %d\n"
        " tm_mday:  %d\n"
        " tm_mon:   %d\n"
        " tm_year:  %d\n"
        " tm_yday:  %d\n"
        " tm_isdst: %d\n\n",
        [rbx].tm.tm_sec,
        [rbx].tm.tm_min,
        [rbx].tm.tm_hour,
        [rbx].tm.tm_mday,
        [rbx].tm.tm_mon,
        [rbx].tm.tm_year,
        [rbx].tm.tm_wday,
        [rbx].tm.tm_yday,
        [rbx].tm.tm_isdst )

   .return( 0 )

_tmain endp

    end _tstart
