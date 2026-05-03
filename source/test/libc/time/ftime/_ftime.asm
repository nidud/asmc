; _FTIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include stdio.inc
include time.inc
include tchar.inc
include sys/timeb.inc

.code

_tmain proc argc:int_t, argv:array_t

    .new tb:_timeb

    .ifsd ( _ftime( &tb ) < 0 )

        perror("_ftime")
    .else
        _tprintf(
            " time     %p\n"
            " millitm  %d\n"
            " timezone %d\n"
            " dstflag  %d\n\n",
            tb.time,
            tb.millitm,
            tb.timezone,
            tb.dstflag
            )
    .endif
    .return( 0 )

_tmain endp

    end _tstart
