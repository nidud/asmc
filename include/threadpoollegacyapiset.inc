ifndef _THREADPOOLLEGACYAPISET_H_
define _THREADPOOLLEGACYAPISET_H_

include apiset.inc
include apisetcconv.inc
include minwindef.inc
include minwinbase.inc

QueueUserWorkItem proto WINAPI :LPTHREAD_START_ROUTINE, :PVOID, :ULONG
UnregisterWaitEx proto WINAPI :HANDLE, :HANDLE

CreateTimerQueue proto WINAPI
CreateTimerQueueTimer proto WINAPI :PHANDLE, :HANDLE, :WAITORTIMERCALLBACK, :PVOID, :DWORD, :DWORD, :ULONG
ChangeTimerQueueTimer proto WINAPI :HANDLE, :HANDLE, :ULONG, :ULONG
DeleteTimerQueueTimer proto WINAPI :HANDLE, :HANDLE, :HANDLE
DeleteTimerQueueEx proto WINAPI :HANDLE, :HANDLE

endif
