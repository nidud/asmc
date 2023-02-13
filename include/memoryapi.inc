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

VirtualAlloc proto WINAPI :LPVOID, :SIZE_T, :DWORD, :DWORD
VirtualProtect proto WINAPI :LPVOID, :SIZE_T, :DWORD, :PDWORD

VirtualFree proto WINAPI :LPVOID, :SIZE_T, :DWORD
VirtualQuery proto WINAPI :LPCVOID, :PMEMORY_BASIC_INFORMATION, :SIZE_T
VirtualAllocEx proto WINAPI :HANDLE, :LPVOID, :SIZE_T, :DWORD, :DWORD
VirtualProtectEx proto WINAPI :HANDLE, :LPVOID, :SIZE_T, :DWORD, :PDWORD

VirtualQueryEx proto WINAPI :HANDLE, :LPCVOID, :PMEMORY_BASIC_INFORMATION, :SIZE_T
ReadProcessMemory proto WINAPI :HANDLE, :LPCVOID, :LPVOID, :SIZE_T, :ptr
WriteProcessMemory proto WINAPI :HANDLE, :LPVOID, :LPCVOID, :SIZE_T, :ptr
CreateFileMappingW proto WINAPI :HANDLE, :LPSECURITY_ATTRIBUTES, :DWORD, :DWORD, :DWORD, :LPCWSTR
ifdef _UNICODE
define CreateFileMapping <CreateFileMappingW>
endif

OpenFileMappingW proto WINAPI :DWORD, :BOOL, :LPCWSTR
ifdef _UNICODE
define OpenFileMapping <OpenFileMappingW>
endif

MapViewOfFile proto WINAPI :HANDLE, :DWORD, :DWORD, :DWORD, :SIZE_T
MapViewOfFileEx proto WINAPI :HANDLE, :DWORD, :DWORD, :DWORD, :SIZE_T, :LPVOID
VirtualFreeEx proto WINAPI :HANDLE, :LPVOID, :SIZE_T, :DWORD
FlushViewOfFile proto WINAPI :LPCVOID, :SIZE_T

UnmapViewOfFile proto WINAPI :LPCVOID

GetLargePageMinimum proto WINAPI
GetProcessWorkingSetSizeEx proto WINAPI :HANDLE, :PSIZE_T, :PSIZE_T, :PDWORD
SetProcessWorkingSetSizeEx proto WINAPI :HANDLE, :SIZE_T, :SIZE_T, :DWORD

VirtualLock proto WINAPI :LPVOID, :SIZE_T
VirtualUnlock proto WINAPI :LPVOID, :SIZE_T

GetWriteWatch proto WINAPI :DWORD, :PVOID, :SIZE_T, :ptr, :ptr, :LPDWORD
ResetWriteWatch proto WINAPI :LPVOID, :SIZE_T

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

GetSystemFileCacheSize proto WINAPI :PSIZE_T, :PSIZE_T, :PDWORD
SetSystemFileCacheSize proto WINAPI :SIZE_T, :SIZE_T, :DWORD

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
NumberOfBytes           SIZE_T ?
_WIN32_MEMORY_RANGE_ENTRY ends
WIN32_MEMORY_RANGE_ENTRY typedef _WIN32_MEMORY_RANGE_ENTRY
PWIN32_MEMORY_RANGE_ENTRY typedef ptr _WIN32_MEMORY_RANGE_ENTRY

PrefetchVirtualMemory proto WINAPI :HANDLE, :ULONG_PTR, :PWIN32_MEMORY_RANGE_ENTRY, :ULONG
endif

if (_WIN32_WINNT ge _WIN32_WINNT_WIN8)
CreateFileMappingFromApp proto WINAPI :HANDLE, :PSECURITY_ATTRIBUTES, :ULONG, :ULONG64, :PCWSTR
MapViewOfFileFromApp proto WINAPI :HANDLE, :ULONG, :ULONG64, :SIZE_T
UnmapViewOfFileEx proto WINAPI :PVOID, :ULONG
endif

if (_WIN32_WINNT ge _WIN32_WINNT_WINXP)
AllocateUserPhysicalPages proto WINAPI :HANDLE, :PULONG_PTR, :PULONG_PTR
FreeUserPhysicalPages proto WINAPI :HANDLE, :PULONG_PTR, :PULONG_PTR
MapUserPhysicalPages proto WINAPI :PVOID, :ULONG_PTR, :PULONG_PTR
endif

if (_WIN32_WINNT ge _WIN32_WINNT_VISTA)
AllocateUserPhysicalPagesNuma proto WINAPI :HANDLE, :PULONG_PTR, :PULONG_PTR, :DWORD
VirtualAllocExNuma proto WINAPI :HANDLE, :LPVOID, :SIZE_T, :DWORD, :DWORD, :DWORD
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

OfferVirtualMemory proto WINAPI :PVOID, :SIZE_T, :OFFER_PRIORITY
ReclaimVirtualMemory proto WINAPI :ptr, :SIZE_T
DiscardVirtualMemory proto WINAPI :PVOID, :SIZE_T

endif
endif

if (_WIN32_WINNT ge _WIN32_WINNT_WIN10)
SetProcessValidCallTargets proto WINAPI :HANDLE, :PVOID, :SIZE_T, :ULONG, :PCFG_CALL_TARGET_INFO
SetProcessValidCallTargetsForMappedView proto WINAPI :HANDLE, :PVOID, :SIZE_T, :ULONG, :PCFG_CALL_TARGET_INFO, :HANDLE, :ULONG64
VirtualAllocFromApp proto WINAPI :PVOID, :SIZE_T, :ULONG, :ULONG
VirtualProtectFromApp proto WINAPI :PVOID, :SIZE_T, :ULONG, :PULONG
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
RegionSize              SIZE_T ?
CommitSize              SIZE_T ?
WIN32_MEMORY_REGION_INFORMATION ends

QueryVirtualMemoryInformation proto WINAPI :HANDLE, :ptr, :WIN32_MEMORY_INFORMATION_CLASS, :PVOID, :SIZE_T, :PSIZE_T

endif

if (NTDDI_VERSION ge NTDDI_WIN10_RS2)
MapViewOfFileNuma2 proto WINAPI :HANDLE, :HANDLE, :ULONG64, :PVOID, :SIZE_T, :ULONG, :ULONG, :ULONG
endif

UnmapViewOfFile2 proto WINAPI :HANDLE, :PVOID, :ULONG
VirtualUnlockEx proto WINAPI :HANDLE, :LPVOID, :SIZE_T

if (NTDDI_VERSION ge NTDDI_WIN10_RS4)

VirtualAlloc2 proto WINAPI :HANDLE, :PVOID, :SIZE_T, :ULONG, :ULONG, :ptr, :ULONG
MapViewOfFile3 proto WINAPI :HANDLE, :HANDLE, :PVOID, :ULONG64, :SIZE_T, :ULONG, :ULONG, :ptr, :ULONG

VirtualAlloc2FromApp proto WINAPI :HANDLE, :PVOID, :SIZE_T, :ULONG, :ULONG, :ptr, :ULONG
MapViewOfFile3FromApp proto WINAPI :HANDLE, :HANDLE, :PVOID, :ULONG64, :SIZE_T, :ULONG, :ULONG, :ptr, :ULONG

endif

if (NTDDI_VERSION ge NTDDI_WIN10_RS5)
CreateFileMapping2 proto WINAPI :HANDLE, :ptr, :ULONG, :ULONG, :ULONG, :ULONG64, :PCWSTR, :ptr, :ULONG
endif

endif
