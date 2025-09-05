ifndef _APISETREALTIME_
define _APISETREALTIME_
ifndef _APIQUERY2_H_
include apiquery2.inc
endif

if (_WIN32_WINNT ge 0x0600)
QueryThreadCycleTime proto WINAPI :HANDLE, :PULONG64
QueryProcessCycleTime proto WINAPI :HANDLE, :PULONG64
QueryIdleProcessorCycleTime proto WINAPI :PULONG, :PULONG64
endif

if (_WIN32_WINNT ge 0x0601)
QueryIdleProcessorCycleTimeEx proto WINAPI :USHORT, :PULONG, :PULONG64
endif

QueryInterruptTimePrecise proto WINAPI :PULONGLONG
QueryUnbiasedInterruptTimePrecise proto WINAPI :PULONGLONG
QueryInterruptTime proto WINAPI :PULONGLONG

if (_WIN32_WINNT ge 0x0601)
QueryUnbiasedInterruptTime proto WINAPI :PULONGLONG
endif

QueryAuxiliaryCounterFrequency proto WINAPI :PULONGLONG
ConvertAuxiliaryCounterToPerformanceCounter proto WINAPI :ULONGLONG, :PULONGLONG, :PULONGLONG
ConvertPerformanceCounterToAuxiliaryCounter proto WINAPI :ULONGLONG, :PULONGLONG, :PULONGLONG

endif
