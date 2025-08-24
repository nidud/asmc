ifndef _HEAPAPI_H_
define _HEAPAPI_H_

include apiset.inc
include apisetcconv.inc
include minwindef.inc
include minwinbase.inc

HEAP_SUMMARY            struct
cb                      DWORD ?
cbAllocated             size_t ?
cbCommitted             size_t ?
cbReserved              size_t ?
cbMaxReserve            size_t ?
HEAP_SUMMARY            ends
PHEAP_SUMMARY           typedef ptr HEAP_SUMMARY
LPHEAP_SUMMARY          typedef ptr HEAP_SUMMARY

HeapCreate proto WINAPI :DWORD, :size_t, :size_t
HeapDestroy proto WINAPI :HANDLE
HeapAlloc proto WINAPI :HANDLE, :DWORD, :size_t
HeapReAlloc proto WINAPI :HANDLE, :DWORD, :ptr, :size_t
HeapFree proto WINAPI :HANDLE, :DWORD, :ptr
HeapSize proto WINAPI :HANDLE, :DWORD, :ptr
GetProcessHeap proto WINAPI
HeapCompact proto WINAPI :HANDLE, :DWORD
HeapSetInformation proto WINAPI :HANDLE, :HEAP_INFORMATION_CLASS, :ptr, :size_t

HeapValidate proto WINAPI :HANDLE, :DWORD, :ptr
HeapSummary proto WINAPI :HANDLE, :DWORD, :LPHEAP_SUMMARY

GetProcessHeaps proto WINAPI :DWORD, :PHANDLE
HeapLock proto WINAPI :HANDLE
HeapUnlock proto WINAPI :HANDLE
HeapWalk proto WINAPI :HANDLE, :LPPROCESS_HEAP_ENTRY
HeapQueryInformation proto WINAPI :HANDLE, :HEAP_INFORMATION_CLASS, :ptr, :size_t, :psize_t

endif
