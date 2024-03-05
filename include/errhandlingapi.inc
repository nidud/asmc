ifndef _ERRHANDLING_H_
define _ERRHANDLING_H_

include apiset.inc
include apisetcconv.inc
include minwindef.inc

.pragma comment(lib, kernel32)

CALLBACK(PTOP_LEVEL_EXCEPTION_FILTER, :ptr)
LPTOP_LEVEL_EXCEPTION_FILTER typedef PTOP_LEVEL_EXCEPTION_FILTER
RaiseException proto WINAPI :DWORD, :DWORD, :DWORD, :ptr

UnhandledExceptionFilter proto WINAPI :ptr
SetUnhandledExceptionFilter proto WINAPI :LPTOP_LEVEL_EXCEPTION_FILTER
ifndef _M_CEE_PURE
GetLastError proto WINAPI
endif
SetLastError proto WINAPI :DWORD
if (_WIN32_WINNT ge 0x0600)
GetErrorMode proto WINAPI
endif
SetErrorMode proto WINAPI :UINT

if (_WIN32_WINNT ge 0x0501)
AddVectoredExceptionHandler proto WINAPI :ULONG, :PVECTORED_EXCEPTION_HANDLER
RemoveVectoredExceptionHandler proto WINAPI :PVOID
AddVectoredContinueHandler proto WINAPI :ULONG, :PVECTORED_EXCEPTION_HANDLER
RemoveVectoredContinueHandler proto WINAPI :PVOID
endif

ifndef RC_INVOKED
ifdef WINBASE_DECLARE_RESTORE_LAST_ERROR

RestoreLastError proto WINAPI :DWORD

CALLBACK(PRESTORE_LAST_ERROR, DWORD)
define RESTORE_LAST_ERROR_NAME_A    <"RestoreLastError">
define RESTORE_LAST_ERROR_NAME_W    <L"RestoreLastError">
define RESTORE_LAST_ERROR_NAME      <"RestoreLastError">

endif
endif

RaiseFailFastException proto WINAPI :PEXCEPTION_RECORD, :PCONTEXT, :DWORD

FatalAppExitA proto WINAPI :UINT, :LPCSTR
FatalAppExitW proto WINAPI :UINT, :LPCWSTR
ifdef _UNICODE
define FatalAppExit  <FatalAppExitW>
else
define FatalAppExit  <FatalAppExitA>
endif

GetThreadErrorMode proto WINAPI
SetThreadErrorMode proto WINAPI :DWORD, :LPDWORD

TerminateProcessOnMemoryExhaustion proto WINAPI :SIZE_T

endif
