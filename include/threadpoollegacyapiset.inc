ifndef _THREADPOOLLEGACYAPISET_H_
define _THREADPOOLLEGACYAPISET_H_
ifndef _APIQUERY2_H_
include apiquery2.inc
endif
ifndef _MINWINBASE_
include minwinbase.inc
endif

QueueUserWorkItem proto WINAPI :LPTHREAD_START_ROUTINE, :PVOID, :ULONG
UnregisterWaitEx proto WINAPI :HANDLE, :HANDLE

CreateTimerQueue proto WINAPI
CreateTimerQueueTimer proto WINAPI :PHANDLE, :HANDLE, :WAITORTIMERCALLBACK, :PVOID, :DWORD, :DWORD, :ULONG
ChangeTimerQueueTimer proto WINAPI :HANDLE, :HANDLE, :ULONG, :ULONG
DeleteTimerQueueTimer proto WINAPI :HANDLE, :HANDLE, :HANDLE
DeleteTimerQueueEx proto WINAPI :HANDLE, :HANDLE

endif
