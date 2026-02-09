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
    xor eax,eax
else
    .new s:SYSTEMTIME
    .new u:SYSTEMTIME

    .ifd FileTimeToSystemTime(ldr(ft), &u)
        .ifd SystemTimeToTzSpecificLocalTime(NULL, &u, &s)
            .return _loctotime_t( s.wYear, s.wMonth, s.wDay, s.wHour, s.wMinute, s.wSecond, -1 )
        .endif
    .endif
endif
    dec rax
    ret

__timet_from_ft endp

    end
