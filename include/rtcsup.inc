ifndef _INC_RTCSUP
define _INC_RTCSUP

ifdef _RTC
ifndef _WIN32
.err <ERROR: Only Win32 target supported!>
endif

include rtcapi.inc

RTCCALLBACK macro a, b:vararg
    exitm<>
    endm

externdef _RTC_api_change_mutex:ptr

else

RTCCALLBACK macro a, b:vararg
    exitm<>
    endm

endif
endif
