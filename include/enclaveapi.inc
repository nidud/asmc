ifndef _ENCLAVEAPI_H_
define _ENCLAVEAPI_H_

include apiset.inc
include apisetcconv.inc
include minwindef.inc
include minwinbase.inc

IsEnclaveTypeSupported proto WINAPI :DWORD
CreateEnclave proto WINAPI :HANDLE, :LPVOID, :size_t, :size_t, :DWORD, :LPCVOID, :DWORD, :LPDWORD
LoadEnclaveData proto WINAPI :HANDLE, :LPVOID, :LPCVOID, :size_t, :DWORD, :LPCVOID, :DWORD, :psize_t, :LPDWORD
InitializeEnclave proto WINAPI :HANDLE, :LPVOID, :LPCVOID, :DWORD, :LPDWORD

LoadEnclaveImageA proto WINAPI :LPVOID, :LPCSTR
LoadEnclaveImageW proto WINAPI :LPVOID, :LPCWSTR
ifdef _UNICODE
define LoadEnclaveImage  <LoadEnclaveImageW>
else
define LoadEnclaveImage  <LoadEnclaveImageA>
endif

CallEnclave proto WINAPI :LPENCLAVE_ROUTINE, :LPVOID, :BOOL, :ptr
TerminateEnclave proto WINAPI :LPVOID, :BOOL
DeleteEnclave proto WINAPI :LPVOID

endif
