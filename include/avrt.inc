ifndef _AVRT_
define _AVRT_
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.enum AVRT_PRIORITY {
    AVRT_PRIORITY_VERYLOW = -2,
    AVRT_PRIORITY_LOW,
    AVRT_PRIORITY_NORMAL,
    AVRT_PRIORITY_HIGH,
    AVRT_PRIORITY_CRITICAL
    }

.enum AVRT_NOTIFICATION {
    AVRT_PROCESS_SUSPEND = 0,
    AVRT_PROCESS_RESUME
    }

THREAD_ORDER_GROUP_INFINITE_TIMEOUT equ (-1)

AvSetMmThreadCharacteristicsA proto WINAPI :LPCSTR, :LPDWORD
AvSetMmThreadCharacteristicsW proto WINAPI :LPCWSTR, :LPDWORD
ifdef _UNICODE
AvSetMmThreadCharacteristics equ <AvSetMmThreadCharacteristicsW>
else
AvSetMmThreadCharacteristics equ <AvSetMmThreadCharacteristicsA>
endif

AvSetMmMaxThreadCharacteristicsA proto WINAPI :LPCSTR, :LPCSTR, :LPDWORD
AvSetMmMaxThreadCharacteristicsW proto WINAPI :LPCWSTR, :LPCWSTR, :LPDWORD
ifdef _UNICODE
AvSetMmMaxThreadCharacteristics equ <AvSetMmMaxThreadCharacteristicsW>
else
AvSetMmMaxThreadCharacteristics equ <AvSetMmMaxThreadCharacteristicsA>
endif

AvRevertMmThreadCharacteristics proto WINAPI :HANDLE
AvSetMmThreadPriority proto WINAPI :HANDLE, :AVRT_PRIORITY
AvRtCreateThreadOrderingGroup proto WINAPI :PHANDLE, :PLARGE_INTEGER, :ptr, :PLARGE_INTEGER
AvRtCreateThreadOrderingGroupExA proto WINAPI :PHANDLE, :PLARGE_INTEGER, :ptr, :PLARGE_INTEGER, :LPCSTR
AvRtCreateThreadOrderingGroupExW proto WINAPI :PHANDLE, :PLARGE_INTEGER, :ptr, :PLARGE_INTEGER, :LPCWSTR
ifdef _UNICODE
AvRtCreateThreadOrderingGroupEx equ <AvRtCreateThreadOrderingGroupExW>
else
AvRtCreateThreadOrderingGroupEx equ <AvRtCreateThreadOrderingGroupExA>
endif

AvRtJoinThreadOrderingGroup proto WINAPI :PHANDLE, :ptr, :BOOL
AvRtWaitOnThreadOrderingGroup proto WINAPI :HANDLE
AvRtLeaveThreadOrderingGroup proto WINAPI :HANDLE
AvRtDeleteThreadOrderingGroup proto WINAPI :HANDLE
AvQuerySystemResponsiveness proto WINAPI :HANDLE, :PULONG

endif

endif
