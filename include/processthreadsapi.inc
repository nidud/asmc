ifndef _PROCESSTHREADSAPI_H_
define _PROCESSTHREADSAPI_H_

include libc.inc

include apiset.inc
include apisetcconv.inc
include minwindef.inc
include minwinbase.inc

_PROCESS_INFORMATION    struct
hProcess                HANDLE ?
hThread                 HANDLE ?
dwProcessId             DWORD ?
dwThreadId              DWORD ?
_PROCESS_INFORMATION    ends
PROCESS_INFORMATION     typedef _PROCESS_INFORMATION
PPROCESS_INFORMATION    typedef ptr _PROCESS_INFORMATION
LPPROCESS_INFORMATION   typedef ptr _PROCESS_INFORMATION

_STARTUPINFOA           struct
cb                      DWORD ?
lpReserved              LPSTR ?
lpDesktop               LPSTR ?
lpTitle                 LPSTR ?
dwX                     DWORD ?
dwY                     DWORD ?
dwXSize                 DWORD ?
dwYSize                 DWORD ?
dwXCountChars           DWORD ?
dwYCountChars           DWORD ?
dwFillAttribute         DWORD ?
dwFlags                 DWORD ?
wShowWindow             WORD ?
cbReserved2             WORD ?
lpReserved2             LPBYTE ?
hStdInput               HANDLE ?
hStdOutput              HANDLE ?
hStdError               HANDLE ?
_STARTUPINFOA           ends
STARTUPINFOA            typedef _STARTUPINFOA
LPSTARTUPINFOA          typedef ptr _STARTUPINFOA
_STARTUPINFOW           struct
cb                      DWORD ?
lpReserved              LPWSTR ?
lpDesktop               LPWSTR ?
lpTitle                 LPWSTR ?
dwX                     DWORD ?
dwY                     DWORD ?
dwXSize                 DWORD ?
dwYSize                 DWORD ?
dwXCountChars           DWORD ?
dwYCountChars           DWORD ?
dwFillAttribute         DWORD ?
dwFlags                 DWORD ?
wShowWindow             WORD ?
cbReserved2             WORD ?
lpReserved2             LPBYTE ?
hStdInput               HANDLE ?
hStdOutput              HANDLE ?
hStdError               HANDLE ?
_STARTUPINFOW           ends
STARTUPINFOW            typedef _STARTUPINFOW
LPSTARTUPINFOW          typedef ptr _STARTUPINFOW
ifdef _UNICODE
STARTUPINFO             typedef STARTUPINFOW
LPSTARTUPINFO           typedef LPSTARTUPINFOW
else
STARTUPINFO             typedef STARTUPINFOA
LPSTARTUPINFO           typedef LPSTARTUPINFOA
endif

if (_WIN32_WINNT ge 0x0400) or (_WIN32_WINDOWS gt 0x0400)
QueueUserAPC proto WINAPI :PAPCFUNC, :HANDLE, :ULONG_PTR
endif

GetProcessTimes proto WINAPI :HANDLE, :LPFILETIME, :LPFILETIME, :LPFILETIME, :LPFILETIME
GetCurrentProcess proto WINAPI
GetCurrentProcessId proto WINAPI
ExitProcess proto WINAPI :UINT
TerminateProcess proto WINAPI :HANDLE, :UINT
GetExitCodeProcess proto WINAPI :HANDLE, :LPDWORD
SwitchToThread proto WINAPI
CreateThread proto WINAPI :LPSECURITY_ATTRIBUTES, :SIZE_T, :LPTHREAD_START_ROUTINE, :LPVOID, :DWORD, :LPDWORD

CreateRemoteThread proto WINAPI :HANDLE, :LPSECURITY_ATTRIBUTES, :SIZE_T, :LPTHREAD_START_ROUTINE, :LPVOID, :DWORD, :LPDWORD

GetCurrentThread proto WINAPI
GetCurrentThreadId proto WINAPI
OpenThread proto WINAPI :DWORD, :BOOL, :DWORD
SetThreadPriority proto WINAPI :HANDLE, :sdword
SetThreadPriorityBoost proto WINAPI :HANDLE, :BOOL
GetThreadPriorityBoost proto WINAPI :HANDLE, :PBOOL
GetThreadPriority proto WINAPI :HANDLE
ExitThread proto WINAPI :DWORD

TerminateThread proto WINAPI :HANDLE, :DWORD

GetExitCodeThread proto WINAPI :HANDLE, :LPDWORD
SuspendThread proto WINAPI :HANDLE
ResumeThread proto WINAPI :HANDLE

ifndef TLS_OUT_OF_INDEXES
define TLS_OUT_OF_INDEXES (0xFFFFFFFF)
endif

TlsAlloc proto WINAPI
TlsGetValue proto WINAPI :DWORD
TlsSetValue proto WINAPI :DWORD, :LPVOID
TlsFree proto WINAPI :DWORD

CreateProcessA proto WINAPI :LPCSTR, :LPSTR, :LPSECURITY_ATTRIBUTES, :LPSECURITY_ATTRIBUTES, :BOOL, :DWORD, :LPVOID, :LPCSTR, :LPSTARTUPINFOA, :LPPROCESS_INFORMATION
CreateProcessW proto WINAPI :LPCWSTR, :LPWSTR, :LPSECURITY_ATTRIBUTES, :LPSECURITY_ATTRIBUTES, :BOOL, :DWORD, :LPVOID, :LPCWSTR, :LPSTARTUPINFOW, :LPPROCESS_INFORMATION
ifdef _UNICODE
define CreateProcess  <CreateProcessW>
else
define CreateProcess  <CreateProcessA>
endif

SetProcessShutdownParameters proto WINAPI :DWORD, :DWORD
GetProcessVersion proto WINAPI :DWORD

GetStartupInfoW proto WINAPI :LPSTARTUPINFOW
ifdef _UNICODE
define GetStartupInfo  <GetStartupInfoW>
endif

CreateProcessAsUserW proto WINAPI :HANDLE, :LPCWSTR, :LPWSTR, :LPSECURITY_ATTRIBUTES, :LPSECURITY_ATTRIBUTES, :BOOL, :DWORD, :LPVOID, :LPCWSTR, :LPSTARTUPINFOW, :LPPROCESS_INFORMATION
ifdef _UNICODE
define CreateProcessAsUser  <CreateProcessAsUserW>
endif

ifndef MIDL_PASS
if (_WIN32_WINNT ge _WIN32_WINNT_WIN8)
GetCurrentProcessToken proto fastcall {
    mov rax,-4
    }
GetCurrentThreadToken proto fastcall {
    mov rax,-5
    }
GetCurrentThreadEffectiveToken proto fastcall {
    mov rax,-6
    }
endif
endif

SetThreadToken proto WINAPI :PHANDLE, :HANDLE
OpenProcessToken proto WINAPI :HANDLE, :DWORD, :PHANDLE
OpenThreadToken proto WINAPI :HANDLE, :DWORD, :BOOL, :PHANDLE
SetPriorityClass proto WINAPI :HANDLE, :DWORD
GetPriorityClass proto WINAPI :HANDLE
SetThreadStackGuarantee proto WINAPI :PULONG
ProcessIdToSessionId proto WINAPI :DWORD, :ptr

LPPROC_THREAD_ATTRIBUTE_LIST typedef ptr _PROC_THREAD_ATTRIBUTE_LIST

if (_WIN32_WINNT ge 0x0501)
GetProcessId proto WINAPI :HANDLE
endif
if (_WIN32_WINNT ge 0x0502)
GetThreadId proto WINAPI :HANDLE
endif
if (_WIN32_WINNT ge 0x0600)
FlushProcessWriteBuffers proto WINAPI
endif

if (_WIN32_WINNT ge 0x0600)

GetProcessIdOfThread proto WINAPI :HANDLE
InitializeProcThreadAttributeList proto WINAPI :LPPROC_THREAD_ATTRIBUTE_LIST, :DWORD, :DWORD, :PSIZE_T
DeleteProcThreadAttributeList proto WINAPI :LPPROC_THREAD_ATTRIBUTE_LIST

define PROC_THREAD_ATTRIBUTE_REPLACE_VALUE     0x00000001

UpdateProcThreadAttribute proto WINAPI :LPPROC_THREAD_ATTRIBUTE_LIST, :DWORD, :DWORD_PTR, :PVOID, :SIZE_T, :PVOID, :PSIZE_T
if (NTDDI_VERSION ge NTDDI_WIN10_VB)
SetProcessDynamicEHContinuationTargets proto WINAPI :HANDLE, :USHORT, :PPROCESS_DYNAMIC_EH_CONTINUATION_TARGET
endif
if (NTDDI_VERSION ge NTDDI_WIN10_VB)
SetProcessDynamicEnforcedCetCompatibleRanges proto WINAPI :HANDLE, :USHORT, :PPROCESS_DYNAMIC_ENFORCED_ADDRESS_RANGE
endif

endif

define PROCESS_AFFINITY_ENABLE_AUTO_UPDATE 0x00000001

SetProcessAffinityUpdateMode proto WINAPI :HANDLE, :DWORD
QueryProcessAffinityUpdateMode proto WINAPI :HANDLE, :LPDWORD

CreateRemoteThreadEx proto WINAPI :HANDLE, :LPSECURITY_ATTRIBUTES, :SIZE_T, :LPTHREAD_START_ROUTINE, :LPVOID, :DWORD, :LPPROC_THREAD_ATTRIBUTE_LIST, :LPDWORD

ifndef MIDL_PASS
if (_WIN32_WINNT ge 0x0602)
GetCurrentThreadStackLimits proto WINAPI :PULONG_PTR, :PULONG_PTR
endif
GetThreadContext proto WINAPI :HANDLE, :LPCONTEXT
endif

if (_WIN32_WINNT ge 0x0602)
GetProcessMitigationPolicy proto WINAPI :HANDLE, :PROCESS_MITIGATION_POLICY, :PVOID, :SIZE_T
endif

SetThreadContext proto WINAPI :HANDLE, :ptr

if (_WIN32_WINNT ge 0x0602)
SetProcessMitigationPolicy proto WINAPI :PROCESS_MITIGATION_POLICY, :PVOID, :SIZE_T
endif

FlushInstructionCache proto WINAPI :HANDLE, :LPCVOID, :SIZE_T

GetThreadTimes proto WINAPI :HANDLE, :LPFILETIME, :LPFILETIME, :LPFILETIME, :LPFILETIME
OpenProcess proto WINAPI :DWORD, :BOOL, :DWORD
IsProcessorFeaturePresent proto WINAPI :DWORD

if (_WIN32_WINNT ge 0x0501)
GetProcessHandleCount proto WINAPI :HANDLE, :PDWORD
endif

if (_WIN32_WINNT ge 0x0502)
GetCurrentProcessorNumber proto WINAPI
endif

if (_WIN32_WINNT ge 0x0601)
SetThreadIdealProcessorEx proto WINAPI :HANDLE, :PPROCESSOR_NUMBER, :PPROCESSOR_NUMBER
GetThreadIdealProcessorEx proto WINAPI :HANDLE, :PPROCESSOR_NUMBER
GetCurrentProcessorNumberEx proto WINAPI :PPROCESSOR_NUMBER
endif

if (_WIN32_WINNT ge _WIN32_WINNT_WINXP)
GetProcessPriorityBoost proto WINAPI :HANDLE, :PBOOL
SetProcessPriorityBoost proto WINAPI :HANDLE, :BOOL
endif

if (_WIN32_WINNT ge _WIN32_WINNT_WINXP)
GetThreadIOPendingFlag proto WINAPI :HANDLE, :PBOOL
endif

if (_WIN32_WINNT ge _WIN32_WINNT_WINXP)
GetSystemTimes proto WINAPI :PFILETIME, :PFILETIME, :PFILETIME
endif

.enum THREAD_INFORMATION_CLASS {
    ThreadMemoryPriority,
    ThreadAbsoluteCpuPriority,
    ThreadDynamicCodePolicy,
    ThreadPowerThrottling,
    ThreadInformationClassMax
    }

if (_WIN32_WINNT ge _WIN32_WINNT_WIN8)
_MEMORY_PRIORITY_INFORMATION struct
MemoryPriority          ULONG ?
_MEMORY_PRIORITY_INFORMATION ends
MEMORY_PRIORITY_INFORMATION typedef _MEMORY_PRIORITY_INFORMATION
PMEMORY_PRIORITY_INFORMATION typedef ptr _MEMORY_PRIORITY_INFORMATION

GetThreadInformation proto WINAPI :HANDLE, :THREAD_INFORMATION_CLASS, :LPVOID, :DWORD
SetThreadInformation proto WINAPI :HANDLE, :THREAD_INFORMATION_CLASS, :LPVOID, :DWORD
endif

;if (_WIN32_WINNT ge _WIN32_WINNT_WIN10_RS3)
if (WDK_NTDDI_VERSION ge NTDDI_WIN10_RS3)

define THREAD_POWER_THROTTLING_CURRENT_VERSION 1
define THREAD_POWER_THROTTLING_EXECUTION_SPEED 0x1
define THREAD_POWER_THROTTLING_VALID_FLAGS (THREAD_POWER_THROTTLING_EXECUTION_SPEED)

_THREAD_POWER_THROTTLING_STATE struct
Version                 ULONG ?
ControlMask             ULONG ?
StateMask               ULONG ?
_THREAD_POWER_THROTTLING_STATE ends
THREAD_POWER_THROTTLING_STATE typedef _THREAD_POWER_THROTTLING_STATE

endif

if (_WIN32_WINNT ge _WIN32_WINNT_WINBLUE)
IsProcessCritical proto WINAPI :HANDLE, :PBOOL
endif
if (_WIN32_WINNT ge _WIN32_WINNT_WIN10)
SetProtectedPolicy proto WINAPI :LPCGUID, :ULONG_PTR, :PULONG_PTR
QueryProtectedPolicy proto WINAPI :LPCGUID, :PULONG_PTR
endif

SetThreadIdealProcessor proto WINAPI :HANDLE, :DWORD

.enum PROCESS_INFORMATION_CLASS {
    ProcessMemoryPriority,
    ProcessMemoryExhaustionInfo,
    ProcessAppMemoryInfo,
    ProcessInPrivateInfo,
    ProcessPowerThrottling,
    ProcessReservedValue1,
    ProcessTelemetryCoverageInfo,
    ProcessProtectionLevelInfo,
    ProcessLeapSecondInfo,
    ProcessInformationClassMax
    }

_APP_MEMORY_INFORMATION struct
AvailableCommit         ULONG64 ?
PrivateCommitUsage      ULONG64 ?
PeakPrivateCommitUsage  ULONG64 ?
TotalCommitUsage        ULONG64 ?
_APP_MEMORY_INFORMATION ends
APP_MEMORY_INFORMATION  typedef _APP_MEMORY_INFORMATION
PAPP_MEMORY_INFORMATION typedef ptr _APP_MEMORY_INFORMATION

define PME_CURRENT_VERSION                      1

.enum PROCESS_MEMORY_EXHAUSTION_TYPE {
    PMETypeFailFastOnCommitFailure,
    PMETypeMax
    }

define PME_FAILFAST_ON_COMMIT_FAIL_DISABLE    0x0
define PME_FAILFAST_ON_COMMIT_FAIL_ENABLE     0x1

_PROCESS_MEMORY_EXHAUSTION_INFO struct
Version                 USHORT ?
Reserved                USHORT ?
Type                    PROCESS_MEMORY_EXHAUSTION_TYPE ?
Value                   ULONG_PTR ?
_PROCESS_MEMORY_EXHAUSTION_INFO ends
PROCESS_MEMORY_EXHAUSTION_INFO typedef _PROCESS_MEMORY_EXHAUSTION_INFO
PPROCESS_MEMORY_EXHAUSTION_INFO typedef ptr _PROCESS_MEMORY_EXHAUSTION_INFO

define PROCESS_POWER_THROTTLING_CURRENT_VERSION 1
define PROCESS_POWER_THROTTLING_EXECUTION_SPEED 0x1
define PROCESS_POWER_THROTTLING_VALID_FLAGS (PROCESS_POWER_THROTTLING_EXECUTION_SPEED)

_PROCESS_POWER_THROTTLING_STATE struct
Version                 ULONG ?
ControlMask             ULONG ?
StateMask               ULONG ?
_PROCESS_POWER_THROTTLING_STATE ends
PROCESS_POWER_THROTTLING_STATE typedef _PROCESS_POWER_THROTTLING_STATE
PPROCESS_POWER_THROTTLING_STATE typedef ptr _PROCESS_POWER_THROTTLING_STATE

PROCESS_PROTECTION_LEVEL_INFORMATION struct
ProtectionLevel         DWORD ?
PROCESS_PROTECTION_LEVEL_INFORMATION ends

define PROCESS_LEAP_SECOND_INFO_FLAG_ENABLE_SIXTY_SECOND   0x1
define PROCESS_LEAP_SECOND_INFO_VALID_FLAGS                (PROCESS_LEAP_SECOND_INFO_FLAG_ENABLE_SIXTY_SECOND)

_PROCESS_LEAP_SECOND_INFO struct
Flags                   ULONG ?
Reserved                ULONG ?
_PROCESS_LEAP_SECOND_INFO ends
PROCESS_LEAP_SECOND_INFO typedef _PROCESS_LEAP_SECOND_INFO
PPROCESS_LEAP_SECOND_INFO typedef ptr _PROCESS_LEAP_SECOND_INFO

if (_WIN32_WINNT ge 0x0602)
SetProcessInformation proto WINAPI :HANDLE, :PROCESS_INFORMATION_CLASS, :LPVOID, :DWORD
GetProcessInformation proto WINAPI :HANDLE, :PROCESS_INFORMATION_CLASS, :LPVOID, :DWORD
endif

if (_WIN32_WINNT ge _WIN32_WINNT_WIN10)
GetSystemCpuSetInformation proto WINAPI :PSYSTEM_CPU_SET_INFORMATION, :ULONG, :PULONG, :HANDLE, :ULONG
GetProcessDefaultCpuSets proto WINAPI :HANDLE, :PULONG, :ULONG, :PULONG
SetProcessDefaultCpuSets proto WINAPI :HANDLE, :ptr, :ULONG
GetThreadSelectedCpuSets proto WINAPI :HANDLE, :PULONG, :ULONG, :PULONG
SetThreadSelectedCpuSets proto WINAPI :HANDLE, :ptr, :ULONG
endif

CreateProcessAsUserA proto WINAPI :HANDLE, :LPCSTR, :LPSTR, :LPSECURITY_ATTRIBUTES, :LPSECURITY_ATTRIBUTES, :BOOL, :DWORD, :LPVOID, :LPCSTR, :LPSTARTUPINFOA, :LPPROCESS_INFORMATION
ifndef _UNICODE
define CreateProcessAsUser  <CreateProcessAsUserA>
endif
GetProcessShutdownParameters proto WINAPI :LPDWORD, :LPDWORD

SetThreadDescription proto WINAPI :HANDLE, :PCWSTR
GetThreadDescription proto WINAPI :HANDLE, :ptr

endif
