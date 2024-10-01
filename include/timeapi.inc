ifndef _TIMERAPI_H_
define _TIMERAPI_H_

include apiset.inc
include apisetcconv.inc

include mmsyscom.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

ifndef MMNOTIMER

define TIMERR_NOERROR   0
define TIMERR_NOCANDO   (TIMERR_BASE+1)
define TIMERR_STRUCT    (TIMERR_BASE+33)

TIMECAPS                struct
wPeriodMin              UINT ?
wPeriodMax              UINT ?
TIMECAPS                ends
PTIMECAPS               typedef ptr TIMECAPS
NPTIMECAPS              typedef ptr TIMECAPS
LPTIMECAPS              typedef ptr TIMECAPS

timeGetSystemTime proto WINAPI :LPMMTIME, :UINT
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)
timeGetTime proto WINAPI
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)
timeGetDevCaps proto WINAPI :LPTIMECAPS, :UINT
timeBeginPeriod proto WINAPI :UINT
timeEndPeriod proto WINAPI :UINT
endif
endif

endif
