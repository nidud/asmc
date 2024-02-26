; _TIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
ifdef __UNIX__
include linux/kernel.inc
else
include winbase.inc
endif

    .code

_time proc uses rbx timeptr:LPTIME

ifndef __UNIX__
  local STime:SYSTEMTIME
endif
    ldr rbx,timeptr
ifdef __UNIX__
    sys_time(rbx)
else
    GetLocalTime( &STime )
    _loctotime_t(
        STime.wYear,
        STime.wMonth,
        STime.wDay,
        STime.wHour,
        STime.wMinute,
        STime.wSecond )
    .if rbx
        mov [rbx],eax
    .endif
endif
    ret

_time endp

    end
