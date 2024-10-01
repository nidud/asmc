ifndef __INC_PROCESSSNAPSHOT
define __INC_PROCESSSNAPSHOT

include libc.inc

.enum PSS_HANDLE_FLAGS {
    PSS_HANDLE_NONE                           = 0x00,
    PSS_HANDLE_HAVE_TYPE                      = 0x01,
    PSS_HANDLE_HAVE_NAME                      = 0x02,
    PSS_HANDLE_HAVE_BASIC_INFORMATION         = 0x04,
    PSS_HANDLE_HAVE_TYPE_SPECIFIC_INFORMATION = 0x08
}

.enum PSS_OBJECT_TYPE {
    PSS_OBJECT_TYPE_UNKNOWN   = 0,
    PSS_OBJECT_TYPE_PROCESS   = 1,
    PSS_OBJECT_TYPE_THREAD    = 2,
    PSS_OBJECT_TYPE_MUTANT    = 3,
    PSS_OBJECT_TYPE_EVENT     = 4,
    PSS_OBJECT_TYPE_SECTION   = 5,
    PSS_OBJECT_TYPE_SEMAPHORE = 6
}

.enum PSS_CAPTURE_FLAGS {
    PSS_CAPTURE_NONE                                = 0x00000000,
    PSS_CAPTURE_VA_CLONE                            = 0x00000001,
    PSS_CAPTURE_RESERVED_00000002                   = 0x00000002,
    PSS_CAPTURE_HANDLES                             = 0x00000004,
    PSS_CAPTURE_HANDLE_NAME_INFORMATION             = 0x00000008,
    PSS_CAPTURE_HANDLE_BASIC_INFORMATION            = 0x00000010,
    PSS_CAPTURE_HANDLE_TYPE_SPECIFIC_INFORMATION    = 0x00000020,
    PSS_CAPTURE_HANDLE_TRACE                        = 0x00000040,
    PSS_CAPTURE_THREADS                             = 0x00000080,
    PSS_CAPTURE_THREAD_CONTEXT                      = 0x00000100,
    PSS_CAPTURE_THREAD_CONTEXT_EXTENDED             = 0x00000200,
    PSS_CAPTURE_RESERVED_00000400                   = 0x00000400,
    PSS_CAPTURE_VA_SPACE                            = 0x00000800,
    PSS_CAPTURE_VA_SPACE_SECTION_INFORMATION        = 0x00001000,
    PSS_CAPTURE_IPT_TRACE                           = 0x00002000,
    PSS_CAPTURE_RESERVED_00004000                   = 0x00004000,

    PSS_CREATE_BREAKAWAY_OPTIONAL                   = 0x04000000,
    PSS_CREATE_BREAKAWAY                            = 0x08000000,
    PSS_CREATE_FORCE_BREAKAWAY                      = 0x10000000,
    PSS_CREATE_USE_VM_ALLOCATIONS                   = 0x20000000,
    PSS_CREATE_MEASURE_PERFORMANCE                  = 0x40000000,
    PSS_CREATE_RELEASE_SECTION                      = 0x80000000
}

define PSS_PERF_RESOLUTION     1000000

.enum PSS_QUERY_INFORMATION_CLASS {
    PSS_QUERY_PROCESS_INFORMATION = 0,
    PSS_QUERY_VA_CLONE_INFORMATION = 1,
    PSS_QUERY_AUXILIARY_PAGES_INFORMATION = 2,
    PSS_QUERY_VA_SPACE_INFORMATION = 3,
    PSS_QUERY_HANDLE_INFORMATION = 4,
    PSS_QUERY_THREAD_INFORMATION = 5,
    PSS_QUERY_HANDLE_TRACE_INFORMATION = 6,
    PSS_QUERY_PERFORMANCE_COUNTERS = 7
}

.enum PSS_WALK_INFORMATION_CLASS {
    PSS_WALK_AUXILIARY_PAGES = 0,
    PSS_WALK_VA_SPACE = 1,
    PSS_WALK_HANDLES = 2,
    PSS_WALK_THREADS = 3
}

.enum PSS_DUPLICATE_FLAGS {
    PSS_DUPLICATE_NONE         = 0x00,
    PSS_DUPLICATE_CLOSE_SOURCE = 0x01
}

DECLARE_HANDLE(HPSS)
DECLARE_HANDLE(HPSSWALK)

.enum PSS_PROCESS_FLAGS {
    PSS_PROCESS_FLAGS_NONE        = 0x00000000,
    PSS_PROCESS_FLAGS_PROTECTED   = 0x00000001,
    PSS_PROCESS_FLAGS_WOW64       = 0x00000002,
    PSS_PROCESS_FLAGS_RESERVED_03 = 0x00000004,
    PSS_PROCESS_FLAGS_RESERVED_04 = 0x00000008,
    PSS_PROCESS_FLAGS_FROZEN      = 0x00000010
}

PSS_PROCESS_INFORMATION struct
ExitStatus              DWORD ?
PebBaseAddress          ptr ?
AffinityMask            ULONG_PTR ?
BasePriority            LONG ?
ProcessId               DWORD ?
ParentProcessId         DWORD ?
Flags                   PSS_PROCESS_FLAGS ?
CreateTime              FILETIME <>
ExitTime                FILETIME <>
KernelTime              FILETIME <>
UserTime                FILETIME <>
PriorityClass           DWORD ?
PeakVirtualSize         ULONG_PTR ?
VirtualSize             ULONG_PTR ?
PageFaultCount          DWORD ?
PeakWorkingSetSize      ULONG_PTR ?
WorkingSetSize          ULONG_PTR ?
QuotaPeakPagedPoolUsage ULONG_PTR ?
QuotaPagedPoolUsage     ULONG_PTR ?
QuotaPeakNonPagedPoolUsage ULONG_PTR ?
QuotaNonPagedPoolUsage  ULONG_PTR ?
PagefileUsage           ULONG_PTR ?
PeakPagefileUsage       ULONG_PTR ?
PrivateUsage            ULONG_PTR ?
ExecuteFlags            DWORD ?
ImageFileName           wchar_t MAX_PATH dup(?)
PSS_PROCESS_INFORMATION ends

PSS_VA_CLONE_INFORMATION struct
VaCloneHandle           HANDLE ?
PSS_VA_CLONE_INFORMATION ends

PSS_AUXILIARY_PAGES_INFORMATION struct
AuxPagesCaptured        DWORD ?
PSS_AUXILIARY_PAGES_INFORMATION ends

PSS_VA_SPACE_INFORMATION struct
RegionCount             DWORD ?
PSS_VA_SPACE_INFORMATION ends

PSS_HANDLE_INFORMATION  struct
HandlesCaptured         DWORD ?
PSS_HANDLE_INFORMATION  ends

PSS_THREAD_INFORMATION  struct
ThreadsCaptured         DWORD ?
ContextLength           DWORD ?
PSS_THREAD_INFORMATION  ends

PSS_HANDLE_TRACE_INFORMATION struct
SectionHandle           HANDLE ?
Size                    DWORD ?
PSS_HANDLE_TRACE_INFORMATION ends

PSS_PERFORMANCE_COUNTERS struct
TotalCycleCount         UINT64 ?
TotalWallClockPeriod    UINT64 ?
VaCloneCycleCount       UINT64 ?
VaCloneWallClockPeriod  UINT64 ?
VaSpaceCycleCount       UINT64 ?
VaSpaceWallClockPeriod  UINT64 ?
AuxPagesCycleCount      UINT64 ?
AuxPagesWallClockPeriod UINT64 ?
HandlesCycleCount       UINT64 ?
HandlesWallClockPeriod  UINT64 ?
ThreadsCycleCount       UINT64 ?
ThreadsWallClockPeriod  UINT64 ?
PSS_PERFORMANCE_COUNTERS ends

PSS_AUXILIARY_PAGE_ENTRY struct
Address                 ptr ?
BasicInformation        MEMORY_BASIC_INFORMATION <>
CaptureTime             FILETIME <>
PageContents            ptr ?
PageSize                DWORD ?
PSS_AUXILIARY_PAGE_ENTRY ends

PSS_VA_SPACE_ENTRY      struct
BaseAddress             ptr ?
AllocationBase          ptr ?
AllocationProtect       DWORD ?
RegionSize              ULONG_PTR ?
State                   DWORD ?
Protect                 DWORD ?
Type                    DWORD ?
TimeDateStamp           DWORD ?
SizeOfImage             DWORD ?
ImageBase               ptr ?
CheckSum                DWORD ?
MappedFileNameLength    WORD ?
MappedFileName          ptr const ?
PSS_VA_SPACE_ENTRY      ends

PSS_HANDLE_ENTRY        struct
Handle                  HANDLE ?
Flags                   PSS_HANDLE_FLAGS ?
ObjectType              PSS_OBJECT_TYPE ?
CaptureTime             FILETIME <>
Attributes              DWORD ?
GrantedAccess           DWORD ?
HandleCount             DWORD ?
PointerCount            DWORD ?
PagedPoolCharge         DWORD ?
NonPagedPoolCharge      DWORD ?
CreationTime            FILETIME <>
TypeNameLength          WORD ?
TypeName                ptr const ?
ObjectNameLength        WORD ?
ObjectName              ptr const ?
union TypeSpecificInformation
 struct Process
  ExitStatus            DWORD ?
  PebBaseAddress        ptr ?
  AffinityMask          ULONG_PTR ?
  BasePriority          LONG ?
  ProcessId             DWORD ?
  ParentProcessId       DWORD ?
  Flags                 DWORD ?
ends
 struct Thread
  ExitStatus            DWORD ?
  TebBaseAddress        ptr ?
  ProcessId             DWORD ?
  ThreadId              DWORD ?
  AffinityMask          ULONG_PTR ?
  Priority              sdword ?
  BasePriority          sdword ?
  Win32StartAddress     ptr ?
ends
 struct Mutant
  CurrentCount          LONG ?
  Abandoned             BOOL ?
  OwnerProcessId        DWORD ?
  OwnerThreadId         DWORD ?
ends
 struct Event
  ManualReset           BOOL ?
  Signaled              BOOL ?
ends
 struct Section
  BaseAddress           ptr ?
  AllocationAttributes  DWORD ?
  MaximumSize           LARGE_INTEGER <>
ends
 struct Semaphore
  CurrentCount          LONG ?
  MaximumCount          LONG ?
ends
ends
PSS_HANDLE_ENTRY        ends

.enum PSS_THREAD_FLAGS {
    PSS_THREAD_FLAGS_NONE       = 0x0000,
    PSS_THREAD_FLAGS_TERMINATED = 0x0001
}

PSS_THREAD_ENTRY        struct
ExitStatus              DWORD ?
TebBaseAddress          ptr ?
ProcessId               DWORD ?
ThreadId                DWORD ?
AffinityMask            ULONG_PTR ?
Priority                sdword ?
BasePriority            sdword ?
LastSyscallFirstArgument ptr ?
LastSyscallNumber       WORD ?
CreateTime              FILETIME <>
ExitTime                FILETIME <>
KernelTime              FILETIME <>
UserTime                FILETIME <>
Win32StartAddress       ptr ?
CaptureTime             FILETIME <>
Flags                   PSS_THREAD_FLAGS ?
SuspendCount            WORD ?
SizeOfContextRecord     WORD ?
ContextRecord           PCONTEXT ?
PSS_THREAD_ENTRY        ends

PSS_ALLOCATOR           struct
Context                 ptr ?
AllocRoutine            proc :ptr, :DWORD
FreeRoutine             proc :ptr, :ptr
PSS_ALLOCATOR           ends

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)
if (NTDDI_VERSION ge NTDDI_WIN8)
PssCaptureSnapshot proto WINAPI :HANDLE, :PSS_CAPTURE_FLAGS, :DWORD, :ptr
PssFreeSnapshot proto WINAPI :HANDLE, :HPSS
PssQuerySnapshot proto WINAPI :HPSS, :PSS_QUERY_INFORMATION_CLASS, :ptr, :DWORD
PssWalkSnapshot proto WINAPI :HPSS, :PSS_WALK_INFORMATION_CLASS, :HPSSWALK, :ptr, :DWORD
PssDuplicateSnapshot proto WINAPI :HANDLE, :HPSS, :HANDLE, :ptr, :PSS_DUPLICATE_FLAGS
PssWalkMarkerCreate proto WINAPI :ptr, :ptr
PssWalkMarkerFree proto WINAPI :HPSSWALK
PssWalkMarkerGetPosition proto WINAPI :HPSSWALK, :ptr
PssWalkMarkerSetPosition proto WINAPI :HPSSWALK, :ULONG_PTR
PssWalkMarkerSeekToBeginning proto WINAPI :HPSSWALK
endif
endif

endif
