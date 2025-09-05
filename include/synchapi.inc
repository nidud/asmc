ifndef _SYNCHAPI_H_
define _SYNCHAPI_H_
ifndef _APIQUERY2_H_
include apiquery2.inc
endif
ifndef _MINWINBASE_
include minwinbase.inc
endif

define SRWLOCK_INIT RTL_SRWLOCK_INIT

SRWLOCK     typedef RTL_SRWLOCK
PSRWLOCK    typedef ptr SRWLOCK

if (_WIN32_WINNT ge 0x0600)
InitializeSRWLock proto WINAPI :PSRWLOCK
ReleaseSRWLockExclusive proto WINAPI :PSRWLOCK
ReleaseSRWLockShared proto WINAPI :PSRWLOCK
AcquireSRWLockExclusive proto WINAPI :PSRWLOCK
AcquireSRWLockShared proto WINAPI :PSRWLOCK
TryAcquireSRWLockExclusive proto WINAPI :PSRWLOCK
TryAcquireSRWLockShared proto WINAPI :PSRWLOCK
endif
if (_WIN32_WINNT lt 0x0600)
InitializeCriticalSection proto WINAPI :LPCRITICAL_SECTION
else
InitializeCriticalSection proto WINAPI :LPCRITICAL_SECTION
endif
EnterCriticalSection proto WINAPI :LPCRITICAL_SECTION
LeaveCriticalSection proto WINAPI :LPCRITICAL_SECTION
InitializeCriticalSectionAndSpinCount proto WINAPI :LPCRITICAL_SECTION, :DWORD
if (_WIN32_WINNT ge 0x0600)
InitializeCriticalSectionEx proto WINAPI :LPCRITICAL_SECTION, :DWORD, :DWORD
endif
SetCriticalSectionSpinCount proto WINAPI :LPCRITICAL_SECTION, :DWORD
if (_WIN32_WINNT ge 0x0400)
TryEnterCriticalSection proto WINAPI :LPCRITICAL_SECTION
endif
DeleteCriticalSection proto WINAPI :LPCRITICAL_SECTION

INIT_ONCE               typedef RTL_RUN_ONCE
PINIT_ONCE              typedef PRTL_RUN_ONCE
LPINIT_ONCE             typedef PRTL_RUN_ONCE

define INIT_ONCE_STATIC_INIT    RTL_RUN_ONCE_INIT
define INIT_ONCE_CHECK_ONLY     RTL_RUN_ONCE_CHECK_ONLY
define INIT_ONCE_ASYNC          RTL_RUN_ONCE_ASYNC
define INIT_ONCE_INIT_FAILED    RTL_RUN_ONCE_INIT_FAILED

define INIT_ONCE_CTX_RESERVED_BITS RTL_RUN_ONCE_CTX_RESERVED_BITS

CALLBACK(PINIT_ONCE_FN, :PINIT_ONCE, :PVOID, :ptr)

if (_WIN32_WINNT ge 0x0600)
InitOnceInitialize proto WINAPI :PINIT_ONCE
InitOnceExecuteOnce proto WINAPI :PINIT_ONCE, :PINIT_ONCE_FN, :PVOID, :ptr
InitOnceBeginInitialize proto WINAPI :LPINIT_ONCE, :DWORD, :PBOOL, :ptr
InitOnceComplete proto WINAPI :LPINIT_ONCE, :DWORD, :LPVOID
endif

CONDITION_VARIABLE      typedef RTL_CONDITION_VARIABLE
PCONDITION_VARIABLE     typedef ptr CONDITION_VARIABLE

define CONDITION_VARIABLE_INIT RTL_CONDITION_VARIABLE_INIT
define CONDITION_VARIABLE_LOCKMODE_SHARED RTL_CONDITION_VARIABLE_LOCKMODE_SHARED

if (_WIN32_WINNT ge 0x0600)
InitializeConditionVariable proto WINAPI :PCONDITION_VARIABLE
WakeConditionVariable proto WINAPI :PCONDITION_VARIABLE
WakeAllConditionVariable proto WINAPI :PCONDITION_VARIABLE
SleepConditionVariableCS proto WINAPI :PCONDITION_VARIABLE, :PCRITICAL_SECTION, :DWORD
SleepConditionVariableSRW proto WINAPI :PCONDITION_VARIABLE, :PSRWLOCK, :DWORD, :ULONG
endif

SetEvent proto WINAPI :HANDLE
ResetEvent proto WINAPI :HANDLE
ReleaseSemaphore proto WINAPI :HANDLE, :LONG, :LPLONG
ReleaseMutex proto WINAPI :HANDLE
WaitForSingleObject proto WINAPI :HANDLE, :DWORD
SleepEx proto WINAPI :DWORD, :BOOL
WaitForSingleObjectEx proto WINAPI :HANDLE, :DWORD, :BOOL
WaitForMultipleObjectsEx proto WINAPI :DWORD, :ptr, :BOOL, :DWORD, :BOOL

define MUTEX_MODIFY_STATE  MUTANT_QUERY_STATE
define MUTEX_ALL_ACCESS    MUTANT_ALL_ACCESS

CreateMutexA proto WINAPI :LPSECURITY_ATTRIBUTES, :BOOL, :LPCSTR
CreateMutexW proto WINAPI :LPSECURITY_ATTRIBUTES, :BOOL, :LPCWSTR
ifdef _UNICODE
define CreateMutex  <CreateMutexW>
else
define CreateMutex  <CreateMutexA>
endif

OpenMutexW proto WINAPI :DWORD, :BOOL, :LPCWSTR
ifdef _UNICODE
define OpenMutex  <OpenMutexW>
endif

CreateEventA proto WINAPI :LPSECURITY_ATTRIBUTES, :BOOL, :BOOL, :LPCSTR
CreateEventW proto WINAPI :LPSECURITY_ATTRIBUTES, :BOOL, :BOOL, :LPCWSTR
ifdef _UNICODE
define CreateEvent  <CreateEventW>
else
define CreateEvent  <CreateEventA>
endif

OpenEventA proto WINAPI :DWORD, :BOOL, :LPCSTR
OpenEventW proto WINAPI :DWORD, :BOOL, :LPCWSTR
ifdef _UNICODE
define OpenEvent  <OpenEventW>
else
define OpenEvent  <OpenEventA>
endif

OpenSemaphoreW proto WINAPI :DWORD, :BOOL, :LPCWSTR
ifdef _UNICODE
define OpenSemaphore  <OpenSemaphoreW>
endif

if (_WIN32_WINNT ge 0x0400) or (_WIN32_WINDOWS gt 0x0400)

CALLBACK(PTIMERAPCROUTINE, :LPVOID, :DWORD, :DWORD)

OpenWaitableTimerW proto WINAPI :DWORD, :BOOL, :LPCWSTR
ifdef _UNICODE
define OpenWaitableTimer  <OpenWaitableTimerW>
endif

if (_WIN32_WINNT ge _WIN32_WINNT_WIN7)
SetWaitableTimerEx proto WINAPI :HANDLE, :ptr, :LONG, :PTIMERAPCROUTINE, :LPVOID, :PREASON_CONTEXT, :ULONG
endif

SetWaitableTimer proto WINAPI :HANDLE, :ptr, :LONG, :PTIMERAPCROUTINE, :LPVOID, :BOOL
CancelWaitableTimer proto WINAPI :HANDLE

if (_WIN32_WINNT ge 0x0600)

define CREATE_MUTEX_INITIAL_OWNER  0x00000001

CreateMutexExA proto WINAPI :LPSECURITY_ATTRIBUTES, :LPCSTR, :DWORD, :DWORD
CreateMutexExW proto WINAPI :LPSECURITY_ATTRIBUTES, :LPCWSTR, :DWORD, :DWORD
ifdef _UNICODE
define CreateMutexEx  <CreateMutexExW>
else
define CreateMutexEx  <CreateMutexExA>
endif

define CREATE_EVENT_MANUAL_RESET   0x00000001
define CREATE_EVENT_INITIAL_SET    0x00000002

CreateEventExA proto WINAPI :LPSECURITY_ATTRIBUTES, :LPCSTR, :DWORD, :DWORD
CreateEventExW proto WINAPI :LPSECURITY_ATTRIBUTES, :LPCWSTR, :DWORD, :DWORD
ifdef _UNICODE
define CreateEventEx  <CreateEventExW>
else
define CreateEventEx  <CreateEventExA>
endif

CreateSemaphoreExW proto WINAPI :LPSECURITY_ATTRIBUTES, :LONG, :LONG, :LPCWSTR, :DWORD, :DWORD
ifdef _UNICODE
define CreateSemaphoreEx  <CreateSemaphoreExW>
endif

define CREATE_WAITABLE_TIMER_MANUAL_RESET  0x00000001
if (_WIN32_WINNT ge _NT_TARGET_VERSION_WIN10_RS4)
define CREATE_WAITABLE_TIMER_HIGH_RESOLUTION 0x00000002
endif

CreateWaitableTimerExW proto WINAPI :LPSECURITY_ATTRIBUTES, :LPCWSTR, :DWORD, :DWORD
ifdef _UNICODE
define CreateWaitableTimerEx  <CreateWaitableTimerExW>
endif

endif

endif

SYNCHRONIZATION_BARRIER typedef RTL_BARRIER
PSYNCHRONIZATION_BARRIER typedef PRTL_BARRIER
LPSYNCHRONIZATION_BARRIER typedef PRTL_BARRIER

define SYNCHRONIZATION_BARRIER_FLAGS_SPIN_ONLY  0x01
define SYNCHRONIZATION_BARRIER_FLAGS_BLOCK_ONLY 0x02
define SYNCHRONIZATION_BARRIER_FLAGS_NO_DELETE  0x04

EnterSynchronizationBarrier proto WINAPI :LPSYNCHRONIZATION_BARRIER, :DWORD
InitializeSynchronizationBarrier proto WINAPI :LPSYNCHRONIZATION_BARRIER, :LONG, :LONG
DeleteSynchronizationBarrier proto WINAPI :LPSYNCHRONIZATION_BARRIER
Sleep proto WINAPI :DWORD
WaitOnAddress proto WINAPI :ptr, :ptr, :size_t, :DWORD
WakeByAddressSingle proto WINAPI :PVOID
WakeByAddressAll proto WINAPI :PVOID

ifndef MIDL_PASS
SignalObjectAndWait proto WINAPI :HANDLE, :HANDLE, :DWORD, :BOOL
endif

WaitForMultipleObjects proto WINAPI :DWORD, :ptr, :BOOL, :DWORD
CreateSemaphoreW proto WINAPI :LPSECURITY_ATTRIBUTES, :LONG, :LONG, :LPCWSTR
ifdef _UNICODE
define CreateSemaphore  <CreateSemaphoreW>
endif

CreateWaitableTimerW proto WINAPI :LPSECURITY_ATTRIBUTES, :BOOL, :LPCWSTR
ifdef _UNICODE
define CreateWaitableTimer  <CreateWaitableTimerW>
endif

endif
