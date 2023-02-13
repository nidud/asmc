ifndef _HEAPAPI_H_
define _HEAPAPI_H_

include apiset.inc
include apisetcconv.inc
include minwindef.inc
include minwinbase.inc

_HEAP_SUMMARY           struct
cb                      DWORD ?
cbAllocated             SIZE_T ?
cbCommitted             SIZE_T ?
cbReserved              SIZE_T ?
cbMaxReserve            SIZE_T ?
_HEAP_SUMMARY           ends
HEAP_SUMMARY            typedef _HEAP_SUMMARY
PHEAP_SUMMARY           typedef ptr _HEAP_SUMMARY
LPHEAP_SUMMARY          typedef PHEAP_SUMMARY

HeapCreate proto WINAPI :DWORD, :SIZE_T, :SIZE_T
HeapDestroy proto WINAPI :HANDLE
HeapAlloc proto WINAPI :HANDLE, :DWORD, :SIZE_T
HeapReAlloc proto WINAPI :HANDLE, :DWORD, :LPVOID, :SIZE_T
HeapFree proto WINAPI :HANDLE, :DWORD, :LPVOID
HeapSize proto WINAPI :HANDLE, :DWORD, :LPCVOID
GetProcessHeap proto WINAPI
HeapCompact proto WINAPI :HANDLE, :DWORD
HeapSetInformation proto WINAPI :HANDLE, :HEAP_INFORMATION_CLASS, :PVOID, :SIZE_T

HeapValidate proto WINAPI :HANDLE, :DWORD, :LPCVOID
HeapSummary proto WINAPI :HANDLE, :DWORD, :LPHEAP_SUMMARY

GetProcessHeaps proto WINAPI :DWORD, :PHANDLE
HeapLock proto WINAPI :HANDLE
HeapUnlock proto WINAPI :HANDLE
HeapWalk proto WINAPI :HANDLE, :LPPROCESS_HEAP_ENTRY
HeapQueryInformation proto WINAPI :HANDLE, :HEAP_INFORMATION_CLASS, :PVOID, :SIZE_T, :PSIZE_T

endif
