; _TIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include winbase.inc

    .code

_time proc timeptr:LPTIME

  local STime:SYSTEMTIME

    GetLocalTime( &STime )
    _loctotime_t(
        STime.wYear,
        STime.wMonth,
        STime.wDay,
        STime.wHour,
        STime.wMinute,
        STime.wSecond )

    mov rcx,timeptr
    .if rcx
        mov [rcx],eax
    .endif
    ret

_time endp

    end
