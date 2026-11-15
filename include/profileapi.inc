ifndef _PROFILEAPI_H_
define _PROFILEAPI_H_
ifndef _APIQUERY2_H_
include apiquery2.inc
endif

QueryPerformanceCounter proto WINAPI :PLARGE_INTEGER
QueryPerformanceFrequency proto WINAPI :PLARGE_INTEGER

endif
