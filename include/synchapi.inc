ifndef _SYNCHAPI_H_
define _SYNCHAPI_H_

include libc.inc
.pragma(comment(lib, kernel32))

include apiset.inc
include apisetcconv.inc
include minwindef.inc
include minwinbase.inc

ifndef _APISET_MINWIN_VERSION
_APISET_MINWIN_VERSION equ 0x0101
endif

ifndef _APISET_SYNCH_VER
ifdef _APISET_MINWIN_VERSION
if _APISET_MINWIN_VERSION GT 0x0100
_APISET_SYNCH_VER equ 0x0200
elseif _APISET_MINWIN_VERSION LE 0x0100
_APISET_SYNCH_VER equ 0x0100
endif
endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

SRWLOCK_INIT            equ RTL_SRWLOCK_INIT
SRWLOCK                 typedef RTL_SRWLOCK
PSRWLOCK                typedef ptr RTL_SRWLOCK

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

if (_WIN32_WINNT GE 0x0600)

;VOID
InitializeSRWLock proto WINAPI \
               SRWLock: PSRWLOCK

;VOID
ReleaseSRWLockExclusive proto WINAPI \
               SRWLock: PSRWLOCK

;VOID
ReleaseSRWLockShared proto WINAPI \
               SRWLock: PSRWLOCK

;VOID
AcquireSRWLockExclusive proto WINAPI \
               SRWLock: PSRWLOCK

;VOID
AcquireSRWLockShared proto WINAPI \
               SRWLock: PSRWLOCK

;BOOLEAN
TryAcquireSRWLockExclusive proto WINAPI \
               SRWLock: PSRWLOCK

;BOOLEAN
TryAcquireSRWLockShared proto WINAPI \
               SRWLock: PSRWLOCK

endif ;; (_WIN32_WINNT GE 0x0600)
endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)


if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
if (_WIN32_WINNT LT 0x0600)
;VOID
InitializeCriticalSection proto WINAPI lpCriticalSection: LPCRITICAL_SECTION
else
InitializeCriticalSection proto WINAPI lpCriticalSection: LPCRITICAL_SECTION
endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
;VOID
EnterCriticalSection proto WINAPI lpCriticalSection: LPCRITICAL_SECTION
LeaveCriticalSection proto WINAPI lpCriticalSection: LPCRITICAL_SECTION
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
;BOOL
InitializeCriticalSectionAndSpinCount proto WINAPI \
     lpCriticalSection: LPCRITICAL_SECTION,
           dwSpinCount: DWORD
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
if (_WIN32_WINNT GE 0x0600)
;BOOL
InitializeCriticalSectionEx proto WINAPI \
     lpCriticalSection: LPCRITICAL_SECTION,
           dwSpinCount: DWORD,
                 Flags: DWORD
endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
;DWORD
SetCriticalSectionSpinCount proto WINAPI \
     lpCriticalSection: LPCRITICAL_SECTION,
           dwSpinCount: DWORD
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
if (_WIN32_WINNT GE 0x0400)
;BOOL
TryEnterCriticalSection proto WINAPI \
     lpCriticalSection: LPCRITICAL_SECTION
endif
;VOID
DeleteCriticalSection proto WINAPI \
     lpCriticalSection: LPCRITICAL_SECTION



INIT_ONCE               typedef RTL_RUN_ONCE
PINIT_ONCE              typedef PRTL_RUN_ONCE
LPINIT_ONCE             typedef PRTL_RUN_ONCE

INIT_ONCE_STATIC_INIT   equ RTL_RUN_ONCE_INIT
INIT_ONCE_CHECK_ONLY    equ RTL_RUN_ONCE_CHECK_ONLY
INIT_ONCE_ASYNC         equ RTL_RUN_ONCE_ASYNC
INIT_ONCE_INIT_FAILED   equ RTL_RUN_ONCE_INIT_FAILED
INIT_ONCE_CTX_RESERVED_BITS equ RTL_RUN_ONCE_CTX_RESERVED_BITS

CALLBACK(PINIT_ONCE_FN, :PINIT_ONCE, :ptr, :ptr)

if (( NOT defined(_CONTRACT_GEN) AND (_WIN32_WINNT GE 0x0600)) OR (_APISET_MINWIN_VERSION GE 0x0101))

;VOID
InitOnceInitialize proto WINAPI \
              InitOnce: PINIT_ONCE

;BOOL
InitOnceExecuteOnce proto WINAPI \
              InitOnce: PINIT_ONCE,
                InitFn: PINIT_ONCE_FN,
             Parameter: PVOID,
               Context: ptr LPVOID

;BOOL
InitOnceBeginInitialize proto WINAPI \
            lpInitOnce: LPINIT_ONCE,
               dwFlags: DWORD,
              fPending: PBOOL,
             lpContext: ptr LPVOID

;BOOL
InitOnceComplete proto WINAPI \
            lpInitOnce: LPINIT_ONCE,
               dwFlags: DWORD,
             lpContext: LPVOID

endif

CONDITION_VARIABLE      typedef RTL_CONDITION_VARIABLE
PCONDITION_VARIABLE     typedef ptr RTL_CONDITION_VARIABLE

CONDITION_VARIABLE_INIT equ RTL_CONDITION_VARIABLE_INIT
CONDITION_VARIABLE_LOCKMODE_SHARED equ RTL_CONDITION_VARIABLE_LOCKMODE_SHARED

if (( NOT defined(_CONTRACT_GEN) AND (_WIN32_WINNT GE 0x0600)) OR (_APISET_MINWIN_VERSION GE 0x0101))

;VOID
InitializeConditionVariable proto WINAPI \
     ConditionVariable: PCONDITION_VARIABLE
;VOID
WakeConditionVariable proto WINAPI \
     ConditionVariable: PCONDITION_VARIABLE
;VOID
WakeAllConditionVariable proto WINAPI \
     ConditionVariable: PCONDITION_VARIABLE
;BOOL
SleepConditionVariableCS proto WINAPI \
     ConditionVariable: PCONDITION_VARIABLE,
       CriticalSection: PCRITICAL_SECTION,
        dwMilliseconds: DWORD
;BOOL
SleepConditionVariableSRW proto WINAPI \
     ConditionVariable: PCONDITION_VARIABLE,
               SRWLock: PSRWLOCK,
        dwMilliseconds: DWORD,
                 Flags: ULONG
endif

;BOOL
SetEvent proto WINAPI \
                hEvent: HANDLE
;BOOL
ResetEvent proto WINAPI \
                hEvent: HANDLE
;BOOL
ReleaseSemaphore proto WINAPI \
            hSemaphore: HANDLE,
         lReleaseCount: LONG,
       lpPreviousCount: LPLONG

;BOOL
ReleaseMutex proto WINAPI \
                hMutex: HANDLE
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

;DWORD
WaitForSingleObject proto WINAPI \
               hHandle: HANDLE,
        dwMilliseconds: DWORD
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

;DWORD
SleepEx proto WINAPI \
        dwMilliseconds: DWORD,
            bAlertable: BOOL
;DWORD
WaitForSingleObjectEx proto WINAPI \
               hHandle: HANDLE,
        dwMilliseconds: DWORD,
            bAlertable: BOOL

;DWORD
WaitForMultipleObjectsEx proto WINAPI \
                nCount: DWORD,
             lpHandles: ptr HANDLE,
              bWaitAll: BOOL,
        dwMilliseconds: DWORD,
            bAlertable: BOOL

MUTEX_MODIFY_STATE      equ MUTANT_QUERY_STATE
MUTEX_ALL_ACCESS        equ MUTANT_ALL_ACCESS

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

;HANDLE
CreateMutexA proto WINAPI \
     lpMutexAttributes: LPSECURITY_ATTRIBUTES,
         bInitialOwner: BOOL,
                lpName: LPCSTR
;HANDLE
CreateMutexW proto WINAPI \
     lpMutexAttributes: LPSECURITY_ATTRIBUTES,
         bInitialOwner: BOOL,
                lpName: LPCWSTR

ifdef _UNICODE
CreateMutex             equ <CreateMutexW>
else
CreateMutex             equ <CreateMutexA>
endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

;HANDLE
OpenMutexW proto WINAPI \
       dwDesiredAccess: DWORD,
        bInheritHandle: BOOL,
                lpName: LPCWSTR

ifdef _UNICODE
OpenMutex               equ <OpenMutexW>
endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

;HANDLE
CreateEventA proto WINAPI \
     lpEventAttributes: LPSECURITY_ATTRIBUTES,
          bManualReset: BOOL,
         bInitialState: BOOL,
                lpName: LPCSTR

;HANDLE
CreateEventW proto WINAPI \
     lpEventAttributes: LPSECURITY_ATTRIBUTES,
          bManualReset: BOOL,
         bInitialState: BOOL,
                lpName: LPCWSTR

ifdef _UNICODE
CreateEvent             equ <CreateEventW>
else
CreateEvent             equ <CreateEventA>
endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

;HANDLE
OpenEventA proto WINAPI \
       dwDesiredAccess: DWORD,
        bInheritHandle: BOOL,
                lpName: LPCSTR

;HANDLE
OpenEventW proto WINAPI \
       dwDesiredAccess: DWORD,
        bInheritHandle: BOOL,
                lpName: LPCWSTR

ifdef _UNICODE
OpenEvent               equ <OpenEventW>
else
OpenEvent               equ <OpenEventA>
endif

;HANDLE
OpenSemaphoreW proto WINAPI \
       dwDesiredAccess: DWORD,
        bInheritHandle: BOOL,
                lpName: LPCWSTR

ifdef _UNICODE
OpenSemaphore           equ <OpenSemaphoreW>
endif
endif

if (_WIN32_WINNT GE 0x0400) OR (_WIN32_WINDOWS GT 0x0400)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

CALLBACK(PTIMERAPCROUTINE, :LPVOID, :DWORD, :DWORD)

;HANDLE
OpenWaitableTimerW proto WINAPI \
       dwDesiredAccess: DWORD,
        bInheritHandle: BOOL,
           lpTimerName: LPCWSTR

ifdef _UNICODE
OpenWaitableTimer       equ <OpenWaitableTimerW>
endif

if (_WIN32_WINNT GE _WIN32_WINNT_WIN7)
;BOOL
SetWaitableTimerEx proto WINAPI \
                hTimer: HANDLE,
             lpDueTime: ptr LARGE_INTEGER,
               lPeriod: LONG,
  pfnCompletionRoutine: PTIMERAPCROUTINE,
lpArgToCompletionRoutine: LPVOID,
           WakeContext: PREASON_CONTEXT,
        TolerableDelay: ULONG
endif

;BOOL
SetWaitableTimer proto WINAPI \
                hTimer: HANDLE,
             lpDueTime: ptr LARGE_INTEGER,
               lPeriod: LONG,
  pfnCompletionRoutine: PTIMERAPCROUTINE,
lpArgToCompletionRoutine: LPVOID,
               fResume: BOOL

;BOOL
CancelWaitableTimer proto WINAPI \
                hTimer: HANDLE

endif ; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)


if (_WIN32_WINNT GE 0x0600)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

CREATE_MUTEX_INITIAL_OWNER equ 0x00000001

;HANDLE
CreateMutexExA proto WINAPI \
     lpMutexAttributes: LPSECURITY_ATTRIBUTES,
                lpName: LPCSTR,
               dwFlags: DWORD,
       dwDesiredAccess: DWORD

;HANDLE
CreateMutexExW proto WINAPI \
     lpMutexAttributes: LPSECURITY_ATTRIBUTES,
                lpName: LPCWSTR,
               dwFlags: DWORD,
       dwDesiredAccess: DWORD

ifdef _UNICODE
CreateMutexEx           equ <CreateMutexExW>
else
CreateMutexEx           equ <CreateMutexExA>
endif

CREATE_EVENT_MANUAL_RESET equ 0x00000001
CREATE_EVENT_INITIAL_SET equ 0x00000002

;HANDLE
CreateEventExA proto WINAPI \
     lpEventAttributes: LPSECURITY_ATTRIBUTES,
                lpName: LPCSTR,
               dwFlags: DWORD,
       dwDesiredAccess: DWORD

;HANDLE
CreateEventExW proto WINAPI \
     lpEventAttributes: LPSECURITY_ATTRIBUTES,
                lpName: LPCWSTR,
               dwFlags: DWORD,
       dwDesiredAccess: DWORD


ifdef _UNICODE
CreateEventEx           equ <CreateEventExW>
else
CreateEventEx           equ <CreateEventExA>
endif

;HANDLE
CreateSemaphoreExW proto WINAPI \
 lpSemaphoreAttributes: LPSECURITY_ATTRIBUTES,
         lInitialCount: LONG,
         lMaximumCount: LONG,
                lpName: LPCWSTR,
               dwFlags: DWORD,
       dwDesiredAccess: DWORD

ifdef _UNICODE
CreateSemaphoreEx       equ <CreateSemaphoreExW>
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

CREATE_WAITABLE_TIMER_MANUAL_RESET equ 0x00000001

;HANDLE
CreateWaitableTimerExW proto WINAPI \
     lpTimerAttributes: LPSECURITY_ATTRIBUTES,
           lpTimerName: LPCWSTR,
               dwFlags: DWORD,
       dwDesiredAccess: DWORD

ifdef _UNICODE
CreateWaitableTimerEx   equ <CreateWaitableTimerExW>
endif

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif ;; (_WIN32_WINNT GE 0x0600)

endif ;; (_WIN32_WINNT GE 0x0400) OR (_WIN32_WINDOWS GT 0x0400)


if NOT defined(_CONTRACT_GEN) OR (_APISET_SYNCH_VER GE 0x0101)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

SYNCHRONIZATION_BARRIER typedef RTL_BARRIER
PSYNCHRONIZATION_BARRIER typedef PRTL_BARRIER
LPSYNCHRONIZATION_BARRIER typedef PRTL_BARRIER

SYNCHRONIZATION_BARRIER_FLAGS_SPIN_ONLY equ 0x01
SYNCHRONIZATION_BARRIER_FLAGS_BLOCK_ONLY equ 0x02
SYNCHRONIZATION_BARRIER_FLAGS_NO_DELETE equ 0x04

;BOOL
EnterSynchronizationBarrier proto WINAPI \
             lpBarrier: LPSYNCHRONIZATION_BARRIER,
               dwFlags: DWORD

;BOOL
InitializeSynchronizationBarrier proto WINAPI \
             lpBarrier: LPSYNCHRONIZATION_BARRIER,
         lTotalThreads: LONG,
            lSpinCount: LONG

;BOOL
DeleteSynchronizationBarrier proto WINAPI \
             lpBarrier: LPSYNCHRONIZATION_BARRIER

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

;VOID
Sleep proto WINAPI \
        dwMilliseconds: DWORD

;BOOL
WaitOnAddress proto WINAPI \
               Address: ptr,
        CompareAddress: PVOID,
           AddressSize: SIZE_T,
        dwMilliseconds: DWORD

;VOID
WakeByAddressSingle proto WINAPI \
               Address: PVOID

;VOID
WakeByAddressAll proto WINAPI \
               Address: PVOID

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef MIDL_PASS

;DWORD
SignalObjectAndWait proto WINAPI \
       hObjectToSignal: HANDLE,
       hObjectToWaitOn: HANDLE,
        dwMilliseconds: DWORD,
            bAlertable: BOOL

endif

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif ;; (_APISET_SYNCH_VER GE 0x0101)

endif ;; _SYNCHAPI_H_
