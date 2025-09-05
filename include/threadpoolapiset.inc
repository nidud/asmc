ifndef _THREADPOOLAPISET_H_
define _THREADPOOLAPISET_H_
ifndef _APIQUERY2_H_
include apiquery2.inc
endif
ifndef _MINWINBASE_
include minwinbase.inc
endif

CALLBACK(PTP_WIN32_IO_CALLBACK, :PTP_CALLBACK_INSTANCE, :PVOID, :PVOID, :ULONG, :ULONG_PTR, :PTP_IO)

if (_WIN32_WINNT ge 0x0600)

CreateThreadpool proto WINAPI :PVOID
SetThreadpoolThreadMaximum proto WINAPI :PTP_POOL, :DWORD
SetThreadpoolThreadMinimum proto WINAPI :PTP_POOL, :DWORD
SetThreadpoolStackInformation proto WINAPI :PTP_POOL, :PTP_POOL_STACK_INFORMATION
QueryThreadpoolStackInformation proto WINAPI :PTP_POOL, :PTP_POOL_STACK_INFORMATION
CloseThreadpool proto WINAPI :PTP_POOL
CreateThreadpoolCleanupGroup proto WINAPI
CloseThreadpoolCleanupGroupMembers proto WINAPI :PTP_CLEANUP_GROUP, :BOOL, :PVOID
CloseThreadpoolCleanupGroup proto WINAPI :PTP_CLEANUP_GROUP
SetEventWhenCallbackReturns proto WINAPI :PTP_CALLBACK_INSTANCE, :HANDLE
ReleaseSemaphoreWhenCallbackReturns proto WINAPI :PTP_CALLBACK_INSTANCE, :HANDLE, :DWORD
ReleaseMutexWhenCallbackReturns proto WINAPI :PTP_CALLBACK_INSTANCE, :HANDLE
LeaveCriticalSectionWhenCallbackReturns proto WINAPI :PTP_CALLBACK_INSTANCE, :PCRITICAL_SECTION
FreeLibraryWhenCallbackReturns proto WINAPI :PTP_CALLBACK_INSTANCE, :HMODULE
CallbackMayRunLong proto WINAPI :PTP_CALLBACK_INSTANCE
DisassociateCurrentThreadFromCallback proto WINAPI :PTP_CALLBACK_INSTANCE
TrySubmitThreadpoolCallback proto WINAPI :PTP_SIMPLE_CALLBACK, :PVOID, :PTP_CALLBACK_ENVIRON
CreateThreadpoolWork proto WINAPI :PTP_WORK_CALLBACK, :PVOID, :PTP_CALLBACK_ENVIRON
SubmitThreadpoolWork proto WINAPI :PTP_WORK
WaitForThreadpoolWorkCallbacks proto WINAPI :PTP_WORK, :BOOL
CloseThreadpoolWork proto WINAPI :PTP_WORK
CreateThreadpoolTimer proto WINAPI :PTP_TIMER_CALLBACK, :PVOID, :PTP_CALLBACK_ENVIRON
SetThreadpoolTimer proto WINAPI :PTP_TIMER, :PFILETIME, :DWORD, :DWORD
IsThreadpoolTimerSet proto WINAPI :PTP_TIMER
WaitForThreadpoolTimerCallbacks proto WINAPI :PTP_TIMER, :BOOL
CloseThreadpoolTimer proto WINAPI :PTP_TIMER
CreateThreadpoolWait proto WINAPI :PTP_WAIT_CALLBACK, :PVOID, :PTP_CALLBACK_ENVIRON
SetThreadpoolWait proto WINAPI :PTP_WAIT, :HANDLE, :PFILETIME
WaitForThreadpoolWaitCallbacks proto WINAPI :PTP_WAIT, :BOOL
CloseThreadpoolWait proto WINAPI :PTP_WAIT
CreateThreadpoolIo proto WINAPI :HANDLE, :PTP_WIN32_IO_CALLBACK, :PVOID, :PTP_CALLBACK_ENVIRON
StartThreadpoolIo proto WINAPI :PTP_IO
CancelThreadpoolIo proto WINAPI :PTP_IO
WaitForThreadpoolIoCallbacks proto WINAPI :PTP_IO, :BOOL
CloseThreadpoolIo proto WINAPI :PTP_IO

endif

SetThreadpoolTimerEx proto WINAPI :PTP_TIMER, :PFILETIME, :DWORD, :DWORD
SetThreadpoolWaitEx proto WINAPI :PTP_WAIT, :HANDLE, :PFILETIME, :PVOID

endif
