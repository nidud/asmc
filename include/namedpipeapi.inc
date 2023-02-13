ifndef _NAMEDPIPE_H_
define _NAMEDPIPE_H_

include apiset.inc
include apisetcconv.inc
include minwindef.inc
include minwinbase.inc

CreatePipe proto WINAPI :PHANDLE, :PHANDLE, :LPSECURITY_ATTRIBUTES, :DWORD
ConnectNamedPipe proto WINAPI :HANDLE, :LPOVERLAPPED
DisconnectNamedPipe proto WINAPI :HANDLE
SetNamedPipeHandleState proto WINAPI :HANDLE, :LPDWORD, :LPDWORD, :LPDWORD
PeekNamedPipe proto WINAPI :HANDLE, :LPVOID, :DWORD, :LPDWORD, :LPDWORD, :LPDWORD

TransactNamedPipe proto WINAPI :HANDLE, :LPVOID, :DWORD, :LPVOID, :DWORD, :LPDWORD, :LPOVERLAPPED

CreateNamedPipeW proto WINAPI :LPCWSTR, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :LPSECURITY_ATTRIBUTES
ifdef _UNICODE
define CreateNamedPipe  <CreateNamedPipeW>
endif
WaitNamedPipeW proto WINAPI :LPCWSTR, :DWORD
ifdef _UNICODE
define WaitNamedPipe  <WaitNamedPipeW>
endif

if (_WIN32_WINNT ge 0x0600)
GetNamedPipeClientComputerNameW proto WINAPI :HANDLE, :LPWSTR, :ULONG
endif
ifdef _UNICODE
define GetNamedPipeClientComputerName  <GetNamedPipeClientComputerNameW>
endif
ImpersonateNamedPipeClient proto WINAPI :HANDLE

GetNamedPipeInfo proto WINAPI :HANDLE, :LPDWORD, :LPDWORD, :LPDWORD, :LPDWORD
GetNamedPipeHandleStateW proto WINAPI :HANDLE, :LPDWORD, :LPDWORD, :LPDWORD, :LPDWORD, :LPWSTR, :DWORD
ifdef _UNICODE
define GetNamedPipeHandleState  <GetNamedPipeHandleStateW>
endif

CallNamedPipeW proto WINAPI :LPCWSTR, :LPVOID, :DWORD, :LPVOID, :DWORD, :LPDWORD, :DWORD
ifdef _UNICODE
define CallNamedPipe  <CallNamedPipeW>
endif

endif
