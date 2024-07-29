; timet_from_ft.asm--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include winbase.inc

    .code

__timet_from_ft proc ft:LPFILETIME

ifdef __UNIX__
    int 3
else

    .new stime:SYSTEMTIME
    .new stUTC:SYSTEMTIME

    .ifd ( !FileTimeToSystemTime(ft, &stUTC) )

        dec rax
       .return
    .endif

    .ifd ( !SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stime) )

        dec rax
       .return
    .endif

    _loctotime_t(stime.wYear,
                 stime.wMonth,
                 stime.wDay,
                 stime.wHour,
                 stime.wMinute,
                 stime.wSecond )
endif
    ret

__timet_from_ft endp

    end
