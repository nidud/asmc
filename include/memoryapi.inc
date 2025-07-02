ifndef _MEMORYAPI_H_
define _MEMORYAPI_H_

include apiset.inc
include apisetcconv.inc
include minwindef.inc
include minwinbase.inc

define FILE_MAP_WRITE            SECTION_MAP_WRITE
define FILE_MAP_READ             SECTION_MAP_READ
define FILE_MAP_ALL_ACCESS       SECTION_ALL_ACCESS
define FILE_MAP_EXECUTE          SECTION_MAP_EXECUTE_EXPLICIT
define FILE_MAP_COPY             0x00000001
define FILE_MAP_RESERVE          0x80000000
define FILE_MAP_TARGETS_INVALID  0x40000000
define FILE_MAP_LARGE_PAGES      0x20000000

VirtualAlloc proto WINAPI :LPVOID, :size_t, :DWORD, :DWORD
VirtualProtect proto WINAPI :LPVOID, :size_t, :DWORD, :PDWORD

VirtualFree proto WINAPI :LPVOID, :size_t, :DWORD
VirtualQuery proto WINAPI :LPCVOID, :PMEMORY_BASIC_INFORMATION, :size_t
VirtualAllocEx proto WINAPI :HANDLE, :LPVOID, :size_t, :DWORD, :DWORD
VirtualProtectEx proto WINAPI :HANDLE, :LPVOID, :size_t, :DWORD, :PDWORD

VirtualQueryEx proto WINAPI :HANDLE, :LPCVOID, :PMEMORY_BASIC_INFORMATION, :size_t
ReadProcessMemory proto WINAPI :HANDLE, :LPCVOID, :LPVOID, :size_t, :ptr
WriteProcessMemory proto WINAPI :HANDLE, :LPVOID, :LPCVOID, :size_t, :ptr
CreateFileMappingW proto WINAPI :HANDLE, :LPSECURITY_ATTRIBUTES, :DWORD, :DWORD, :DWORD, :LPCWSTR
ifdef _UNICODE
define CreateFileMapping <CreateFileMappingW>
endif

OpenFileMappingW proto WINAPI :DWORD, :BOOL, :LPCWSTR
ifdef _UNICODE
define OpenFileMapping <OpenFileMappingW>
endif

MapViewOfFile proto WINAPI :HANDLE, :DWORD, :DWORD, :DWORD, :size_t
MapViewOfFileEx proto WINAPI :HANDLE, :DWORD, :DWORD, :DWORD, :size_t, :LPVOID
VirtualFreeEx proto WINAPI :HANDLE, :LPVOID, :size_t, :DWORD
FlushViewOfFile proto WINAPI :LPCVOID, :size_t

UnmapViewOfFile proto WINAPI :LPCVOID

GetLargePageMinimum proto WINAPI
GetProcessWorkingSetSizeEx proto WINAPI :HANDLE, :psize_t, :psize_t, :PDWORD
SetProcessWorkingSetSizeEx proto WINAPI :HANDLE, :size_t, :size_t, :DWORD

VirtualLock proto WINAPI :ptr, :size_t
VirtualUnlock proto WINAPI :ptr, :size_t

GetWriteWatch proto WINAPI :DWORD, :ptr, :size_t, :ptr, :ptr, :LPDWORD
ResetWriteWatch proto WINAPI :ptr, :size_t

if (_WIN32_WINNT ge _WIN32_WINNT_WINXP)

.enum MEMORY_RESOURCE_NOTIFICATION_TYPE {
    LowMemoryResourceNotification,
    HighMemoryResourceNotification
    }

CreateMemoryResourceNotification proto WINAPI :MEMORY_RESOURCE_NOTIFICATION_TYPE
QueryMemoryResourceNotification proto WINAPI :HANDLE, :PBOOL

endif

if (_WIN32_WINNT ge _WIN32_WINNT_WS03)

define FILE_CACHE_FLAGS_DEFINED
define FILE_CACHE_MAX_HARD_ENABLE      0x00000001
define FILE_CACHE_MAX_HARD_DISABLE     0x00000002
define FILE_CACHE_MIN_HARD_ENABLE      0x00000004
define FILE_CACHE_MIN_HARD_DISABLE     0x00000008

GetSystemFileCacheSize proto WINAPI :psize_t, :psize_t, :PDWORD
SetSystemFileCacheSize proto WINAPI :size_t, :size_t, :DWORD

endif

if (_WIN32_WINNT ge _WIN32_WINNT_VISTA)
CreateFileMappingNumaW proto WINAPI :HANDLE, :LPSECURITY_ATTRIBUTES, :DWORD, :DWORD, :DWORD, :LPCWSTR, :DWORD
ifdef _UNICODE
define CreateFileMappingNuma <CreateFileMappingNumaW>
endif
endif

if (_WIN32_WINNT ge _WIN32_WINNT_WIN8)
_WIN32_MEMORY_RANGE_ENTRY struct
VirtualAddress          PVOID ?
NumberOfBytes           size_t ?
_WIN32_MEMORY_RANGE_ENTRY ends
WIN32_MEMORY_RANGE_ENTRY typedef _WIN32_MEMORY_RANGE_ENTRY
PWIN32_MEMORY_RANGE_ENTRY typedef ptr _WIN32_MEMORY_RANGE_ENTRY

PrefetchVirtualMemory proto WINAPI :HANDLE, :ULONG_PTR, :PWIN32_MEMORY_RANGE_ENTRY, :ULONG
endif

if (_WIN32_WINNT ge _WIN32_WINNT_WIN8)
CreateFileMappingFromApp proto WINAPI :HANDLE, :PSECURITY_ATTRIBUTES, :ULONG, :ULONG64, :PCWSTR
MapViewOfFileFromApp proto WINAPI :HANDLE, :ULONG, :ULONG64, :size_t
UnmapViewOfFileEx proto WINAPI :PVOID, :ULONG
endif

if (_WIN32_WINNT ge _WIN32_WINNT_WINXP)
AllocateUserPhysicalPages proto WINAPI :HANDLE, :PULONG_PTR, :PULONG_PTR
FreeUserPhysicalPages proto WINAPI :HANDLE, :PULONG_PTR, :PULONG_PTR
MapUserPhysicalPages proto WINAPI :PVOID, :ULONG_PTR, :PULONG_PTR
endif

if (_WIN32_WINNT ge _WIN32_WINNT_VISTA)
AllocateUserPhysicalPagesNuma proto WINAPI :HANDLE, :PULONG_PTR, :PULONG_PTR, :DWORD
VirtualAllocExNuma proto WINAPI :HANDLE, :LPVOID, :size_t, :DWORD, :DWORD, :DWORD
endif

if (_WIN32_WINNT ge _WIN32_WINNT_WIN8)

define MEHC_PATROL_SCRUBBER_PRESENT  0x1

GetMemoryErrorHandlingCapabilities proto WINAPI :PULONG

CALLBACK(BAD_MEMORY_CALLBACK_ROUTINE)
PBAD_MEMORY_CALLBACK_ROUTINE typedef ptr BAD_MEMORY_CALLBACK_ROUTINE

RegisterBadMemoryNotification proto WINAPI :PBAD_MEMORY_CALLBACK_ROUTINE
UnregisterBadMemoryNotification proto WINAPI :PVOID

endif

if (_WIN32_WINNT ge _WIN32_WINNT_WINBLUE)
if ((NTDDI_VERSION gt NTDDI_WINBLUE) or (NTDDI_VERSION eq NTDDI_WINBLUE and defined(WINBLUE_KBSPRING14)))

.enum OFFER_PRIORITY {
    VmOfferPriorityVeryLow = 1,
    VmOfferPriorityLow,
    VmOfferPriorityBelowNormal,
    VmOfferPriorityNormal
    }

OfferVirtualMemory proto WINAPI :ptr, :size_t, :OFFER_PRIORITY
ReclaimVirtualMemory proto WINAPI :ptr, :size_t
DiscardVirtualMemory proto WINAPI :ptr, :size_t

endif
endif

if (_WIN32_WINNT ge _WIN32_WINNT_WIN10)
SetProcessValidCallTargets proto WINAPI :HANDLE, :ptr, :size_t, :ULONG, :PCFG_CALL_TARGET_INFO
SetProcessValidCallTargetsForMappedView proto WINAPI :HANDLE, :PVOID, :size_t, :ULONG, :PCFG_CALL_TARGET_INFO, :HANDLE, :ULONG64
VirtualAllocFromApp proto WINAPI :PVOID, :size_t, :ULONG, :ULONG
VirtualProtectFromApp proto WINAPI :PVOID, :size_t, :ULONG, :PULONG
OpenFileMappingFromApp proto WINAPI :ULONG, :BOOL, :PCWSTR
endif

if (NTDDI_VERSION ge NTDDI_WIN10_RS1)

.enum WIN32_MEMORY_INFORMATION_CLASS {
    MemoryRegionInfo
    }


WIN32_MEMORY_REGION_INFORMATION struct
AllocationBase          PVOID ?
AllocationProtect       ULONG ?
union
 Flags                  ULONG ?
 struct
  record
   _Private             ULONG :  1 ?
   MappedDataFile       ULONG :  1 ?
   MappedImage          ULONG :  1 ?
   MappedPageFile       ULONG :  1 ?
   MappedPhysical       ULONG :  1 ?
   DirectMapped         ULONG :  1 ?
   Reserved             ULONG : 26 ?
  ends
 ends
ends
RegionSize              size_t ?
CommitSize              size_t ?
WIN32_MEMORY_REGION_INFORMATION ends

QueryVirtualMemoryInformation proto WINAPI :HANDLE, :ptr, :WIN32_MEMORY_INFORMATION_CLASS, :ptr, :size_t, :psize_t

endif

if (NTDDI_VERSION ge NTDDI_WIN10_RS2)
MapViewOfFileNuma2 proto WINAPI :HANDLE, :HANDLE, :ULONG64, :ptr, :size_t, :ULONG, :ULONG, :ULONG
endif

UnmapViewOfFile2 proto WINAPI :HANDLE, :ptr, :ULONG
VirtualUnlockEx proto WINAPI :HANDLE, :ptr, :size_t

if (NTDDI_VERSION ge NTDDI_WIN10_RS4)

VirtualAlloc2 proto WINAPI :HANDLE, :PVOID, :size_t, :ULONG, :ULONG, :ptr, :ULONG
MapViewOfFile3 proto WINAPI :HANDLE, :HANDLE, :PVOID, :ULONG64, :size_t, :ULONG, :ULONG, :ptr, :ULONG

VirtualAlloc2FromApp proto WINAPI :HANDLE, :ptr, :size_t, :ULONG, :ULONG, :ptr, :ULONG
MapViewOfFile3FromApp proto WINAPI :HANDLE, :HANDLE, :ptr, :ULONG64, :size_t, :ULONG, :ULONG, :ptr, :ULONG

endif

if (NTDDI_VERSION ge NTDDI_WIN10_RS5)
CreateFileMapping2 proto WINAPI :HANDLE, :ptr, :ULONG, :ULONG, :ULONG, :ULONG64, :PCWSTR, :ptr, :ULONG
endif

endif
