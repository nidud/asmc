ifndef _PROFILEAPI_H_
define _PROFILEAPI_H_

include apiset.inc
include apisetcconv.inc
include minwindef.inc

QueryPerformanceCounter proto WINAPI :ptr
QueryPerformanceFrequency proto WINAPI :ptr

endif
