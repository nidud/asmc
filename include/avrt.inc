include winapifamily.inc
ifndef _AVRT_
_AVRT_ equ <>

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

AvSetMmThreadCharacteristicsA proto WINAPI \
              TaskName: LPCSTR,
             TaskIndex: LPDWORD

AvSetMmThreadCharacteristicsW proto WINAPI \
              TaskName: LPCWSTR,
             TaskIndex: LPDWORD

ifdef _UNICODE
AvSetMmThreadCharacteristics equ <AvSetMmThreadCharacteristicsW>
else
AvSetMmThreadCharacteristics equ <AvSetMmThreadCharacteristicsA>
endif

AvSetMmMaxThreadCharacteristicsA proto WINAPI \
             FirstTask: LPCSTR,
            SecondTask: LPCSTR,
             TaskIndex: LPDWORD

AvSetMmMaxThreadCharacteristicsW proto WINAPI \
             FirstTask: LPCWSTR,
            SecondTask: LPCWSTR,
             TaskIndex: LPDWORD

ifdef _UNICODE
AvSetMmMaxThreadCharacteristics equ <AvSetMmMaxThreadCharacteristicsW>
else
AvSetMmMaxThreadCharacteristics equ <AvSetMmMaxThreadCharacteristicsA>
endif

AvRevertMmThreadCharacteristics proto WINAPI \
            AvrtHandle: HANDLE


AvSetMmThreadPriority proto WINAPI \
            AvrtHandle: HANDLE,
              Priority: AVRT_PRIORITY


AvRtCreateThreadOrderingGroup proto WINAPI \
               Context: PHANDLE,
                Period: PLARGE_INTEGER,
    ThreadOrderingGuid: ptr GUID,
               Timeout: PLARGE_INTEGER


AvRtCreateThreadOrderingGroupExA proto WINAPI \
               Context: PHANDLE,
                Period: PLARGE_INTEGER,
    ThreadOrderingGuid: ptr GUID,
               Timeout: PLARGE_INTEGER,
              TaskName: LPCSTR

AvRtCreateThreadOrderingGroupExW proto WINAPI \
               Context: PHANDLE,
                Period: PLARGE_INTEGER,
    ThreadOrderingGuid: ptr GUID,
               Timeout: PLARGE_INTEGER,
              TaskName: LPCWSTR

ifdef _UNICODE
AvRtCreateThreadOrderingGroupEx equ <AvRtCreateThreadOrderingGroupExW>
else
AvRtCreateThreadOrderingGroupEx equ <AvRtCreateThreadOrderingGroupExA>
endif

AvRtJoinThreadOrderingGroup proto WINAPI \
               Context: PHANDLE,
    ThreadOrderingGuid: ptr GUID,
                Before: BOOL

AvRtWaitOnThreadOrderingGroup proto WINAPI \
               Context: HANDLE

AvRtLeaveThreadOrderingGroup proto WINAPI \
               Context: HANDLE

AvRtDeleteThreadOrderingGroup proto WINAPI \
               Context: HANDLE

AvQuerySystemResponsiveness proto WINAPI \
            AvrtHandle: HANDLE,
SystemResponsivenessValue: PULONG

endif

endif ;; _AVRT_
