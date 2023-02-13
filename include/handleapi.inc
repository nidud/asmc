ifndef _APISETHANDLE_
define _APISETHANDLE_

include apiset.inc
include apisetcconv.inc
include minwindef.inc

define INVALID_HANDLE_VALUE (-1)

.pragma(comment(lib, kernel32))

CloseHandle proto WINAPI :HANDLE
DuplicateHandle proto WINAPI :HANDLE, :HANDLE, :HANDLE, :LPHANDLE, :DWORD, :BOOL, :DWORD
CompareObjectHandles proto WINAPI :HANDLE, :HANDLE
GetHandleInformation proto WINAPI :HANDLE, :LPDWORD
SetHandleInformation proto WINAPI :HANDLE, :DWORD, :DWORD

endif
