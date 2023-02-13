ifndef _IO_APISET_H_
define _IO_APISET_H_

include apiset.inc
include apisetcconv.inc
include minwindef.inc
include minwinbase.inc

CreateIoCompletionPort proto WINAPI :HANDLE, :HANDLE, :ULONG_PTR, :DWORD
GetQueuedCompletionStatus proto WINAPI :HANDLE, :LPDWORD, :PULONG_PTR, :ptr, :DWORD
if (_WIN32_WINNT ge 0x0600)
GetQueuedCompletionStatusEx proto WINAPI :HANDLE, :LPOVERLAPPED_ENTRY, :ULONG, :PULONG, :DWORD, :BOOL
endif
PostQueuedCompletionStatus proto WINAPI :HANDLE, :DWORD, :ULONG_PTR, :LPOVERLAPPED
DeviceIoControl proto WINAPI :HANDLE, :DWORD, :LPVOID, :DWORD, :LPVOID, :DWORD, :LPDWORD, :LPOVERLAPPED
GetOverlappedResult proto WINAPI :HANDLE, :LPOVERLAPPED, :LPDWORD, :BOOL
if (_WIN32_WINNT ge 0x0600)
CancelIoEx proto WINAPI :HANDLE, :LPOVERLAPPED
endif

CancelIo proto WINAPI :HANDLE
GetOverlappedResultEx proto WINAPI :HANDLE, :LPOVERLAPPED, :LPDWORD, :DWORD, :BOOL

if (_WIN32_WINNT ge 0x0600)
CancelSynchronousIo proto WINAPI :HANDLE
endif

endif
