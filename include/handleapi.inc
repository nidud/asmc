ifndef _APISETHANDLE_
define _APISETHANDLE_
ifndef _APIQUERY2_H_
include apiquery2.inc
endif

define INVALID_HANDLE_VALUE (-1)

.pragma(comment(lib, kernel32))

CloseHandle proto WINAPI :HANDLE
DuplicateHandle proto WINAPI :HANDLE, :HANDLE, :HANDLE, :LPHANDLE, :DWORD, :BOOL, :DWORD
CompareObjectHandles proto WINAPI :HANDLE, :HANDLE
GetHandleInformation proto WINAPI :HANDLE, :LPDWORD
SetHandleInformation proto WINAPI :HANDLE, :DWORD, :DWORD

endif
