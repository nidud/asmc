ifndef _PROCESSENV_
define _PROCESSENV_
ifndef _APIQUERY2_H_
include apiquery2.inc
endif

SetEnvironmentStringsW proto WINAPI :LPWCH
ifdef _UNICODE
define SetEnvironmentStrings  <SetEnvironmentStringsW>
endif

GetStdHandle proto WINAPI :DWORD
SetStdHandle proto WINAPI :DWORD, :HANDLE
if (_WIN32_WINNT ge 0x0600)
SetStdHandleEx proto WINAPI :DWORD, :HANDLE, :PHANDLE
endif

GetCommandLineA proto WINAPI
GetCommandLineW proto WINAPI
ifdef _UNICODE
define GetCommandLine  <GetCommandLineW>
else
define GetCommandLine  <GetCommandLineA>
endif

GetEnvironmentStringsW proto WINAPI
ifdef _UNICODE
define GetEnvironmentStrings  <GetEnvironmentStringsW>
else
GetEnvironmentStrings proto WINAPI
define GetEnvironmentStringsA  <GetEnvironmentStrings>
endif

FreeEnvironmentStringsA proto WINAPI :LPCH
FreeEnvironmentStringsW proto WINAPI :LPWCH
ifdef _UNICODE
define FreeEnvironmentStrings  <FreeEnvironmentStringsW>
else
define FreeEnvironmentStrings  <FreeEnvironmentStringsA>
endif

GetEnvironmentVariableA proto WINAPI :LPCSTR, :LPSTR, :DWORD
GetEnvironmentVariableW proto WINAPI :LPCWSTR, :LPWSTR, :DWORD
ifdef _UNICODE
define GetEnvironmentVariable  <GetEnvironmentVariableW>
else
define GetEnvironmentVariable  <GetEnvironmentVariableA>
endif

SetEnvironmentVariableA proto WINAPI :LPCSTR, :LPCSTR
SetEnvironmentVariableW proto WINAPI :LPCWSTR, :LPCWSTR
ifdef _UNICODE
define SetEnvironmentVariable  <SetEnvironmentVariableW>
else
define SetEnvironmentVariable  <SetEnvironmentVariableA>
endif

ExpandEnvironmentStringsA proto WINAPI :LPCSTR, :LPSTR, :DWORD
ExpandEnvironmentStringsW proto WINAPI :LPCWSTR, :LPWSTR, :DWORD
ifdef _UNICODE
define ExpandEnvironmentStrings  <ExpandEnvironmentStringsW>
else
define ExpandEnvironmentStrings  <ExpandEnvironmentStringsA>
endif

SetCurrentDirectoryA proto WINAPI :LPCSTR
SetCurrentDirectoryW proto WINAPI :LPCWSTR
ifdef _UNICODE
define SetCurrentDirectory  <SetCurrentDirectoryW>
else
define SetCurrentDirectory  <SetCurrentDirectoryA>
endif

GetCurrentDirectoryA proto WINAPI :DWORD, :LPSTR
GetCurrentDirectoryW proto WINAPI :DWORD, :LPWSTR
ifdef _UNICODE
define GetCurrentDirectory  <GetCurrentDirectoryW>
else
define GetCurrentDirectory  <GetCurrentDirectoryA>
endif

SearchPathW proto WINAPI :LPCWSTR, :LPCWSTR, :LPCWSTR, :DWORD, :LPWSTR, :ptr
ifdef _UNICODE
define SearchPath  <SearchPathW>
else
define SearchPath  <SearchPathA>
endif
SearchPathA proto WINAPI :LPCSTR, :LPCSTR, :LPCSTR, :DWORD, :LPSTR, :ptr

if _WIN32_WINNT ge 0x0502
NeedCurrentDirectoryForExePathA proto WINAPI :LPCSTR
NeedCurrentDirectoryForExePathW proto WINAPI :LPCWSTR
ifdef _UNICODE
define NeedCurrentDirectoryForExePath  <NeedCurrentDirectoryForExePathW>
else
define NeedCurrentDirectoryForExePath  <NeedCurrentDirectoryForExePathA>
endif
endif

endif
