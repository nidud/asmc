ifndef _APISETDEBUG_
define _APISETDEBUG_

include apiset.inc
include apisetcconv.inc
include minwindef.inc
include minwinbase.inc

if (_WIN32_WINNT ge 0x0400) or (_WIN32_WINDOWS gt 0x0400)
IsDebuggerPresent proto WINAPI
endif

DebugBreak proto WINAPI
OutputDebugStringA proto WINAPI :LPCSTR
OutputDebugStringW proto WINAPI :LPCWSTR
ifdef _UNICODE
define OutputDebugString  <OutputDebugStringW>
else
define OutputDebugString  <OutputDebugStringA>
endif

ContinueDebugEvent proto WINAPI :DWORD, :DWORD, :DWORD
WaitForDebugEvent proto WINAPI :LPDEBUG_EVENT, :DWORD
DebugActiveProcess proto WINAPI :DWORD
DebugActiveProcessStop proto WINAPI :DWORD

if (_WIN32_WINNT ge 0x0501)
CheckRemoteDebuggerPresent proto WINAPI :HANDLE, :PBOOL
endif
WaitForDebugEventEx proto WINAPI :LPDEBUG_EVENT, :DWORD

endif
