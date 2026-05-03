ifndef _MINIDUMP_H
define _MINIDUMP_H
ifndef _PROCESSTHREADSAPI_H_
include processthreadsapi.inc
endif
ifndef _TIMEZONEAPI_H_
include timezoneapi.inc
endif
ifndef _WINVER_
include winver.inc
endif

ifdef _CONTRACT_GEN
include nt.inc
include ntrtl.inc
include nturtl.inc
include windows.inc
endif
include apiset.inc
include apisetcconv.inc
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_GAMES)
.pragma pack(push, 4)
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

define MINIDUMP_SIGNATURE ('PMDM')
define MINIDUMP_VERSION	  (42899)

RVA	typedef DWORD
RVA64	typedef QWORD

MINIDUMP_LOCATION_DESCRIPTOR struct
DataSize		dd ?
Rva			dd ?
MINIDUMP_LOCATION_DESCRIPTOR ends

MINIDUMP_LOCATION_DESCRIPTOR64 struct
DataSize		dq ?
Rva			dq ?
MINIDUMP_LOCATION_DESCRIPTOR64 ends

MINIDUMP_MEMORY_DESCRIPTOR struct
StartOfMemoryRange	dq ?
Memory			MINIDUMP_LOCATION_DESCRIPTOR <>
MINIDUMP_MEMORY_DESCRIPTOR ends
PMINIDUMP_MEMORY_DESCRIPTOR typedef ptr MINIDUMP_MEMORY_DESCRIPTOR

MINIDUMP_MEMORY_DESCRIPTOR64 struct
StartOfMemoryRange	dq ?
DataSize		dq ?
MINIDUMP_MEMORY_DESCRIPTOR64 ends
PMINIDUMP_MEMORY_DESCRIPTOR64 typedef ptr MINIDUMP_MEMORY_DESCRIPTOR64

MINIDUMP_HEADER		struct
Signature		dd ?
Version			dd ?
NumberOfStreams		dd ?
StreamDirectoryRva	dd ?
CheckSum		dd ?
union
 Reserved		dd ?
 TimeDateStamp		dd ?
ends
Flags			dq ?
MINIDUMP_HEADER		ends
PMINIDUMP_HEADER	typedef ptr MINIDUMP_HEADER

MINIDUMP_DIRECTORY	struct
StreamType		dd ?
Location		MINIDUMP_LOCATION_DESCRIPTOR <>
MINIDUMP_DIRECTORY	ends
PMINIDUMP_DIRECTORY	typedef ptr MINIDUMP_DIRECTORY

MINIDUMP_STRING		struct
Length			dd ?
Buffer			dw 0 dup(?)
MINIDUMP_STRING		ends
PMINIDUMP_STRING	typedef ptr MINIDUMP_STRING

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

.enum MINIDUMP_STREAM_TYPE {
    UnusedStream		= 0,
    ReservedStream0		= 1,
    ReservedStream1		= 2,
    ThreadListStream		= 3,
    ModuleListStream		= 4,
    MemoryListStream		= 5,
    ExceptionStream		= 6,
    SystemInfoStream		= 7,
    ThreadExListStream		= 8,
    Memory64ListStream		= 9,
    CommentStreamA		= 10,
    CommentStreamW		= 11,
    HandleDataStream		= 12,
    FunctionTableStream		= 13,
    UnloadedModuleListStream	= 14,
    MiscInfoStream		= 15,
    MemoryInfoListStream	= 16,
    ThreadInfoListStream	= 17,
    HandleOperationListStream	= 18,
    TokenStream			= 19,
    JavaScriptDataStream	= 20,
    SystemMemoryInfoStream	= 21,
    ProcessVmCountersStream	= 22,
    IptTraceStream		= 23,
    ThreadNamesStream		= 24,

    ceStreamNull		= 0x8000,
    ceStreamSystemInfo		= 0x8001,
    ceStreamException		= 0x8002,
    ceStreamModuleList		= 0x8003,
    ceStreamProcessList		= 0x8004,
    ceStreamThreadList		= 0x8005,
    ceStreamThreadContextList	= 0x8006,
    ceStreamThreadCallStackList = 0x8007,
    ceStreamMemoryVirtualList	= 0x8008,
    ceStreamMemoryPhysicalList	= 0x8009,
    ceStreamBucketParameters	= 0x800A,
    ceStreamProcessModuleMap	= 0x800B,
    ceStreamDiagnosisList	= 0x800C,

    LastReservedStream		= 0xffff
    }

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

CPU_INFORMATION		union
struct X86CpuInfo
 VendorId		dd 3 dup(?)
 VersionInformation	dd ?
 FeatureInformation	dd ?
 AMDExtendedCpuFeatures dd ?
ends
struct OtherCpuInfo
 ProcessorFeatures	dq 2 dup(?)
ends
CPU_INFORMATION		ends
PCPU_INFORMATION	typedef ptr CPU_INFORMATION

MINIDUMP_SYSTEM_INFO	struct
ProcessorArchitecture	dw ?
ProcessorLevel		dw ?
ProcessorRevision	dw ?
union
 Reserved0		dw ?
 struct
  NumberOfProcessors	db ?
  ProductType		db ?
 ends
ends
MajorVersion		dd ?
MinorVersion		dd ?
BuildNumber		dd ?
PlatformId		dd ?
CSDVersionRva		dd ?
union
 Reserved1		dd ?
 struct
  SuiteMask		dw ?
  Reserved2		dw ?
 ends
ends
Cpu			CPU_INFORMATION <>
MINIDUMP_SYSTEM_INFO	ends
PMINIDUMP_SYSTEM_INFO	typedef ptr MINIDUMP_SYSTEM_INFO

C_ASSERT (sizeof(PROCESS_INFORMATION.dwThreadId) eq 4)

MINIDUMP_THREAD		struct
ThreadId		dd ?
SuspendCount		dd ?
PriorityClass		dd ?
Priority		dd ?
Teb			dq ?
Stack			MINIDUMP_MEMORY_DESCRIPTOR <>
ThreadContext		MINIDUMP_LOCATION_DESCRIPTOR <>
MINIDUMP_THREAD		ends
PMINIDUMP_THREAD	typedef ptr MINIDUMP_THREAD

MINIDUMP_THREAD_LIST	struct
NumberOfThreads		dd ?
Threads			MINIDUMP_THREAD 0 dup(?)
MINIDUMP_THREAD_LIST	ends
PMINIDUMP_THREAD_LIST	typedef ptr MINIDUMP_THREAD_LIST

MINIDUMP_THREAD_EX	struct
ThreadId		dd ?
SuspendCount		dd ?
PriorityClass		dd ?
Priority		dd ?
Teb			dq ?
Stack			MINIDUMP_MEMORY_DESCRIPTOR <>
ThreadContext		MINIDUMP_LOCATION_DESCRIPTOR <>
BackingStore		MINIDUMP_MEMORY_DESCRIPTOR <>
MINIDUMP_THREAD_EX	ends
PMINIDUMP_THREAD_EX	typedef ptr MINIDUMP_THREAD_EX

MINIDUMP_THREAD_EX_LIST struct
NumberOfThreads		dd ?
Threads			MINIDUMP_THREAD_EX 0 dup(?)
MINIDUMP_THREAD_EX_LIST ends
PMINIDUMP_THREAD_EX_LIST typedef ptr MINIDUMP_THREAD_EX_LIST

MINIDUMP_EXCEPTION	struct
ExceptionCode		dd ?
ExceptionFlags		dd ?
ExceptionRecord		dq ?
ExceptionAddress	dq ?
NumberParameters	dd ?
__unusedAlignment	dd ?
ExceptionInformation	dq EXCEPTION_MAXIMUM_PARAMETERS dup(?)
MINIDUMP_EXCEPTION	ends
PMINIDUMP_EXCEPTION	typedef ptr MINIDUMP_EXCEPTION

MINIDUMP_EXCEPTION_STREAM struct
ThreadId		dd ?
__alignment		dd ?
ExceptionRecord		MINIDUMP_EXCEPTION <>
ThreadContext		MINIDUMP_LOCATION_DESCRIPTOR <>
MINIDUMP_EXCEPTION_STREAM ends
PMINIDUMP_EXCEPTION_STREAM typedef ptr MINIDUMP_EXCEPTION_STREAM

MINIDUMP_MODULE		struct
BaseOfImage		dq ?
SizeOfImage		dd ?
CheckSum		dd ?
TimeDateStamp		dd ?
ModuleNameRva		dd ?
VersionInfo		VS_FIXEDFILEINFO <>
CvRecord		MINIDUMP_LOCATION_DESCRIPTOR <>
MiscRecord		MINIDUMP_LOCATION_DESCRIPTOR <>
Reserved0		dq ?
Reserved1		dq ?
MINIDUMP_MODULE		ends
PMINIDUMP_MODULE	typedef ptr MINIDUMP_MODULE

MINIDUMP_MODULE_LIST	struct
NumberOfModules		dd ?
Modules			MINIDUMP_MODULE 0 dup(?)
MINIDUMP_MODULE_LIST	ends
PMINIDUMP_MODULE_LIST	typedef ptr MINIDUMP_MODULE_LIST

MINIDUMP_MEMORY_LIST	struct
NumberOfMemoryRanges	dd ?
MemoryRanges		MINIDUMP_MEMORY_DESCRIPTOR 0 dup(?)
MINIDUMP_MEMORY_LIST	ends
PMINIDUMP_MEMORY_LIST	typedef ptr MINIDUMP_MEMORY_LIST

MINIDUMP_MEMORY64_LIST	struct
NumberOfMemoryRanges	dq ?
BaseRva			dq ?
MemoryRanges		MINIDUMP_MEMORY_DESCRIPTOR64 0 dup(?)
MINIDUMP_MEMORY64_LIST	ends
PMINIDUMP_MEMORY64_LIST typedef ptr MINIDUMP_MEMORY64_LIST

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_GAMES)

MINIDUMP_EXCEPTION_INFORMATION struct
ThreadId		dd ?
ExceptionPointers	PEXCEPTION_POINTERS ?
ClientPointers		BOOL ?
MINIDUMP_EXCEPTION_INFORMATION ends
PMINIDUMP_EXCEPTION_INFORMATION typedef ptr MINIDUMP_EXCEPTION_INFORMATION

MINIDUMP_EXCEPTION_INFORMATION64 struct
ThreadId		dd ?
ExceptionRecord		dq ?
ContextRecord		dq ?
ClientPointers		BOOL ?
MINIDUMP_EXCEPTION_INFORMATION64 ends
PMINIDUMP_EXCEPTION_INFORMATION64 typedef ptr MINIDUMP_EXCEPTION_INFORMATION64

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.enum MINIDUMP_HANDLE_OBJECT_INFORMATION_TYPE {
    MiniHandleObjectInformationNone,
    MiniThreadInformation1,
    MiniMutantInformation1,
    MiniMutantInformation2,
    MiniProcessInformation1,
    MiniProcessInformation2,
    MiniEventInformation1,
    MiniSectionInformation1,
    MiniSemaphoreInformation1,
    MiniHandleObjectInformationTypeMax
    }

MINIDUMP_HANDLE_OBJECT_INFORMATION struct
NextInfoRva		dd ?
InfoType		dd ?
SizeOfInfo		dd ?
MINIDUMP_HANDLE_OBJECT_INFORMATION ends

MINIDUMP_HANDLE_DESCRIPTOR struct
Handle			dq ?
TypeNameRva		dd ?
ObjectNameRva		dd ?
Attributes		dd ?
GrantedAccess		dd ?
HandleCount		dd ?
PointerCount		dd ?
MINIDUMP_HANDLE_DESCRIPTOR ends
PMINIDUMP_HANDLE_DESCRIPTOR typedef ptr MINIDUMP_HANDLE_DESCRIPTOR

MINIDUMP_HANDLE_DESCRIPTOR_2 struct
Handle			dq ?
TypeNameRva		dd ?
ObjectNameRva		dd ?
Attributes		dd ?
GrantedAccess		dd ?
HandleCount		dd ?
PointerCount		dd ?
ObjectInfoRva		dd ?
Reserved0		dd ?
MINIDUMP_HANDLE_DESCRIPTOR_2 ends
PMINIDUMP_HANDLE_DESCRIPTOR_2 typedef ptr MINIDUMP_HANDLE_DESCRIPTOR_2

MINIDUMP_HANDLE_DESCRIPTOR_N typedef MINIDUMP_HANDLE_DESCRIPTOR_2
PMINIDUMP_HANDLE_DESCRIPTOR_N typedef ptr MINIDUMP_HANDLE_DESCRIPTOR_N

MINIDUMP_HANDLE_DATA_STREAM struct
SizeOfHeader		dd ?
SizeOfDescriptor	dd ?
NumberOfDescriptors	dd ?
Reserved		dd ?
MINIDUMP_HANDLE_DATA_STREAM ends
PMINIDUMP_HANDLE_DATA_STREAM typedef ptr MINIDUMP_HANDLE_DATA_STREAM

MINIDUMP_HANDLE_OPERATION_LIST struct
SizeOfHeader		dd ?
SizeOfEntry		dd ?
NumberOfEntries		dd ?
Reserved		dd ?
MINIDUMP_HANDLE_OPERATION_LIST ends
PMINIDUMP_HANDLE_OPERATION_LIST typedef ptr MINIDUMP_HANDLE_OPERATION_LIST

MINIDUMP_FUNCTION_TABLE_DESCRIPTOR struct
MinimumAddress		dq ?
MaximumAddress		dq ?
BaseAddress		dq ?
EntryCount		dd ?
SizeOfAlignPad		dd ?
MINIDUMP_FUNCTION_TABLE_DESCRIPTOR ends
PMINIDUMP_FUNCTION_TABLE_DESCRIPTOR typedef ptr MINIDUMP_FUNCTION_TABLE_DESCRIPTOR

MINIDUMP_FUNCTION_TABLE_STREAM struct
SizeOfHeader		dd ?
SizeOfDescriptor	dd ?
SizeOfNativeDescriptor	dd ?
SizeOfFunctionEntry	dd ?
NumberOfDescriptors	dd ?
SizeOfAlignPad		dd ?
MINIDUMP_FUNCTION_TABLE_STREAM ends
PMINIDUMP_FUNCTION_TABLE_STREAM typedef ptr MINIDUMP_FUNCTION_TABLE_STREAM

MINIDUMP_UNLOADED_MODULE struct
BaseOfImage		dq ?
SizeOfImage		dd ?
CheckSum		dd ?
TimeDateStamp		dd ?
ModuleNameRva		RVA ?
MINIDUMP_UNLOADED_MODULE ends
PMINIDUMP_UNLOADED_MODULE typedef ptr MINIDUMP_UNLOADED_MODULE

MINIDUMP_UNLOADED_MODULE_LIST struct
SizeOfHeader		dd ?
SizeOfEntry		dd ?
NumberOfEntries		dd ?
MINIDUMP_UNLOADED_MODULE_LIST ends
PMINIDUMP_UNLOADED_MODULE_LIST typedef ptr MINIDUMP_UNLOADED_MODULE_LIST

XSTATE_CONFIG_FEATURE_MSC_INFO struct
SizeOfInfo		dd ?
ContextSize		dd ?
EnabledFeatures		dq ?
Features		XSTATE_FEATURE MAXIMUM_XSTATE_FEATURES dup(<>)
XSTATE_CONFIG_FEATURE_MSC_INFO ends
PXSTATE_CONFIG_FEATURE_MSC_INFO typedef ptr XSTATE_CONFIG_FEATURE_MSC_INFO

define MINIDUMP_MISC1_PROCESS_ID	    0x00000001
define MINIDUMP_MISC1_PROCESS_TIMES	    0x00000002
define MINIDUMP_MISC1_PROCESSOR_POWER_INFO  0x00000004
define MINIDUMP_MISC3_PROCESS_INTEGRITY	    0x00000010
define MINIDUMP_MISC3_PROCESS_EXECUTE_FLAGS 0x00000020
define MINIDUMP_MISC3_TIMEZONE		    0x00000040
define MINIDUMP_MISC3_PROTECTED_PROCESS	    0x00000080
define MINIDUMP_MISC4_BUILDSTRING	    0x00000100
define MINIDUMP_MISC5_PROCESS_COOKIE	    0x00000200

MINIDUMP_MISC_INFO	struct
SizeOfInfo		dd ?
Flags1			dd ?
ProcessId		dd ?
ProcessCreateTime	dd ?
ProcessUserTime		dd ?
ProcessKernelTime	dd ?
MINIDUMP_MISC_INFO	ends
PMINIDUMP_MISC_INFO	typedef ptr MINIDUMP_MISC_INFO

MINIDUMP_MISC_INFO_2	struct
SizeOfInfo		dd ?
Flags1			dd ?
ProcessId		dd ?
ProcessCreateTime	dd ?
ProcessUserTime		dd ?
ProcessKernelTime	dd ?
ProcessorMaxMhz		dd ?
ProcessorCurrentMhz	dd ?
ProcessorMhzLimit	dd ?
ProcessorMaxIdleState	dd ?
ProcessorCurrentIdleState dd ?
MINIDUMP_MISC_INFO_2	ends
PMINIDUMP_MISC_INFO_2	typedef ptr MINIDUMP_MISC_INFO_2

MINIDUMP_MISC_INFO_3	struct
SizeOfInfo		dd ?
Flags1			dd ?
ProcessId		dd ?
ProcessCreateTime	dd ?
ProcessUserTime		dd ?
ProcessKernelTime	dd ?
ProcessorMaxMhz		dd ?
ProcessorCurrentMhz	dd ?
ProcessorMhzLimit	dd ?
ProcessorMaxIdleState	dd ?
ProcessorCurrentIdleState dd ?
ProcessIntegrityLevel	dd ?
ProcessExecuteFlags	dd ?
ProtectedProcess	dd ?
TimeZoneId		dd ?
TimeZone		TIME_ZONE_INFORMATION <>
MINIDUMP_MISC_INFO_3	ends
PMINIDUMP_MISC_INFO_3	typedef ptr MINIDUMP_MISC_INFO_3

MINIDUMP_MISC_INFO_4	struct
SizeOfInfo		dd ?
Flags1			dd ?
ProcessId		dd ?
ProcessCreateTime	dd ?
ProcessUserTime		dd ?
ProcessKernelTime	dd ?
ProcessorMaxMhz		dd ?
ProcessorCurrentMhz	dd ?
ProcessorMhzLimit	dd ?
ProcessorMaxIdleState	dd ?
ProcessorCurrentIdleState dd ?
ProcessIntegrityLevel	dd ?
ProcessExecuteFlags	dd ?
ProtectedProcess	dd ?
TimeZoneId		dd ?
TimeZone		TIME_ZONE_INFORMATION <>
BuildString		dw MAX_PATH dup(?)
DbgBldStr		dw 40 dup(?)
MINIDUMP_MISC_INFO_4	ends
PMINIDUMP_MISC_INFO_4	typedef ptr MINIDUMP_MISC_INFO_4

MINIDUMP_MISC_INFO_5	struct
SizeOfInfo		dd ?
Flags1			dd ?
ProcessId		dd ?
ProcessCreateTime	dd ?
ProcessUserTime		dd ?
ProcessKernelTime	dd ?
ProcessorMaxMhz		dd ?
ProcessorCurrentMhz	dd ?
ProcessorMhzLimit	dd ?
ProcessorMaxIdleState	dd ?
ProcessorCurrentIdleState dd ?
ProcessIntegrityLevel	dd ?
ProcessExecuteFlags	dd ?
ProtectedProcess	dd ?
TimeZoneId		dd ?
TimeZone		TIME_ZONE_INFORMATION <>
BuildString		dw MAX_PATH dup(?)
DbgBldStr		dw 40 dup(?)
XStateData		XSTATE_CONFIG_FEATURE_MSC_INFO <>
ProcessCookie		dd ?
MINIDUMP_MISC_INFO_5	ends
PMINIDUMP_MISC_INFO_5	typedef ptr MINIDUMP_MISC_INFO_5

MINIDUMP_MISC_INFO_N	typedef MINIDUMP_MISC_INFO_5
PMINIDUMP_MISC_INFO_N	typedef ptr MINIDUMP_MISC_INFO_N

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_GAMES)

MINIDUMP_MEMORY_INFO	struct
BaseAddress		dq ?
AllocationBase		dq ?
AllocationProtect	dd ?
__alignment1		dd ?
RegionSize		dq ?
State			dd ?
Protect			dd ?
Type			dd ?
__alignment2		dd ?
MINIDUMP_MEMORY_INFO	ends
PMINIDUMP_MEMORY_INFO	typedef ptr MINIDUMP_MEMORY_INFO

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

MINIDUMP_MEMORY_INFO_LIST struct
SizeOfHeader		dd ?
SizeOfEntry		dd ?
NumberOfEntries		dq ?
MINIDUMP_MEMORY_INFO_LIST ends
PMINIDUMP_MEMORY_INFO_LIST typedef ptr MINIDUMP_MEMORY_INFO_LIST

MINIDUMP_THREAD_NAME	struct
ThreadId		dd ?
RvaOfThreadName		dq ?
MINIDUMP_THREAD_NAME	ends
PMINIDUMP_THREAD_NAME	typedef ptr MINIDUMP_THREAD_NAME

MINIDUMP_THREAD_NAME_LIST struct
NumberOfThreadNames	dd ?
ThreadNames		MINIDUMP_THREAD_NAME 0 dup(?)
MINIDUMP_THREAD_NAME_LIST ends
PMINIDUMP_THREAD_NAME_LIST typedef ptr MINIDUMP_THREAD_NAME_LIST

define MINIDUMP_THREAD_INFO_ERROR_THREAD    0x00000001
define MINIDUMP_THREAD_INFO_WRITING_THREAD  0x00000002
define MINIDUMP_THREAD_INFO_EXITED_THREAD   0x00000004
define MINIDUMP_THREAD_INFO_INVALID_INFO    0x00000008
define MINIDUMP_THREAD_INFO_INVALID_CONTEXT 0x00000010
define MINIDUMP_THREAD_INFO_INVALID_TEB	    0x00000020

MINIDUMP_THREAD_INFO	struct
ThreadId		dd ?
DumpFlags		dd ?
DumpError		dd ?
ExitStatus		dd ?
CreateTime		dq ?
ExitTime		dq ?
KernelTime		dq ?
UserTime		dq ?
StartAddress		dq ?
Affinity		dq ?
MINIDUMP_THREAD_INFO	ends
PMINIDUMP_THREAD_INFO	typedef ptr MINIDUMP_THREAD_INFO

MINIDUMP_THREAD_INFO_LIST struct
SizeOfHeader		dd ?
SizeOfEntry		dd ?
NumberOfEntries		dd ?
MINIDUMP_THREAD_INFO_LIST ends
PMINIDUMP_THREAD_INFO_LIST typedef ptr MINIDUMP_THREAD_INFO_LIST

MINIDUMP_TOKEN_INFO_HEADER struct
TokenSize		dd ?
TokenId			dd ?
TokenHandle		dq ?
MINIDUMP_TOKEN_INFO_HEADER ends
PMINIDUMP_TOKEN_INFO_HEADER typedef ptr MINIDUMP_TOKEN_INFO_HEADER

MINIDUMP_TOKEN_INFO_LIST struct
TokenListSize		dd ?
TokenListEntries	dd ?
ListHeaderSize		dd ?
ElementHeaderSize	dd ?
MINIDUMP_TOKEN_INFO_LIST ends
PMINIDUMP_TOKEN_INFO_LIST typedef ptr MINIDUMP_TOKEN_INFO_LIST

MINIDUMP_SYSTEM_BASIC_INFORMATION struct
TimerResolution		dd ?
PageSize		dd ?
NumberOfPhysicalPages	dd ?
LowestPhysicalPageNumber dd ?
HighestPhysicalPageNumber dd ?
AllocationGranularity	dd ?
MinimumUserModeAddress	dq ?
MaximumUserModeAddress	dq ?
ActiveProcessorsAffinityMask dq ?
NumberOfProcessors	dd ?
MINIDUMP_SYSTEM_BASIC_INFORMATION ends
PMINIDUMP_SYSTEM_BASIC_INFORMATION typedef ptr MINIDUMP_SYSTEM_BASIC_INFORMATION

MINIDUMP_SYSTEM_FILECACHE_INFORMATION struct
CurrentSize		dq ?
PeakSize		dq ?
PageFaultCount		dd ?
MinimumWorkingSet	dq ?
MaximumWorkingSet	dq ?
CurrentSizeIncludingTransitionInPages dq ?
PeakSizeIncludingTransitionInPages dq ?
TransitionRePurposeCount dd ?
Flags			dd ?
MINIDUMP_SYSTEM_FILECACHE_INFORMATION ends
PMINIDUMP_SYSTEM_FILECACHE_INFORMATION typedef ptr MINIDUMP_SYSTEM_FILECACHE_INFORMATION

MINIDUMP_SYSTEM_BASIC_PERFORMANCE_INFORMATION struct
AvailablePages		dq ?
CommittedPages		dq ?
CommitLimit		dq ?
PeakCommitment		dq ?
MINIDUMP_SYSTEM_BASIC_PERFORMANCE_INFORMATION ends
PMINIDUMP_SYSTEM_BASIC_PERFORMANCE_INFORMATION typedef ptr MINIDUMP_SYSTEM_BASIC_PERFORMANCE_INFORMATION

MINIDUMP_SYSTEM_PERFORMANCE_INFORMATION struct
IdleProcessTime		dq ?
IoReadTransferCount	dq ?
IoWriteTransferCount	dq ?
IoOtherTransferCount	dq ?
IoReadOperationCount	dd ?
IoWriteOperationCount	dd ?
IoOtherOperationCount	dd ?
AvailablePages		dd ?
CommittedPages		dd ?
CommitLimit		dd ?
PeakCommitment		dd ?
PageFaultCount		dd ?
CopyOnWriteCount	dd ?
TransitionCount		dd ?
CacheTransitionCount	dd ?
DemandZeroCount		dd ?
PageReadCount		dd ?
PageReadIoCount		dd ?
CacheReadCount		dd ?
CacheIoCount		dd ?
DirtyPagesWriteCount	dd ?
DirtyWriteIoCount	dd ?
MappedPagesWriteCount	dd ?
MappedWriteIoCount	dd ?
PagedPoolPages		dd ?
NonPagedPoolPages	dd ?
PagedPoolAllocs		dd ?
PagedPoolFrees		dd ?
NonPagedPoolAllocs	dd ?
NonPagedPoolFrees	dd ?
FreeSystemPtes		dd ?
ResidentSystemCodePage	dd ?
TotalSystemDriverPages	dd ?
TotalSystemCodePages	dd ?
NonPagedPoolLookasideHits dd ?
PagedPoolLookasideHits	dd ?
AvailablePagedPoolPages dd ?
ResidentSystemCachePage dd ?
ResidentPagedPoolPage	dd ?
ResidentSystemDriverPage dd ?
CcFastReadNoWait	dd ?
CcFastReadWait		dd ?
CcFastReadResourceMiss	dd ?
CcFastReadNotPossible	dd ?
CcFastMdlReadNoWait	dd ?
CcFastMdlReadWait	dd ?
CcFastMdlReadResourceMiss dd ?
CcFastMdlReadNotPossible dd ?
CcMapDataNoWait		dd ?
CcMapDataWait		dd ?
CcMapDataNoWaitMiss	dd ?
CcMapDataWaitMiss	dd ?
CcPinMappedDataCount	dd ?
CcPinReadNoWait		dd ?
CcPinReadWait		dd ?
CcPinReadNoWaitMiss	dd ?
CcPinReadWaitMiss	dd ?
CcCopyReadNoWait	dd ?
CcCopyReadWait		dd ?
CcCopyReadNoWaitMiss	dd ?
CcCopyReadWaitMiss	dd ?
CcMdlReadNoWait		dd ?
CcMdlReadWait		dd ?
CcMdlReadNoWaitMiss	dd ?
CcMdlReadWaitMiss	dd ?
CcReadAheadIos		dd ?
CcLazyWriteIos		dd ?
CcLazyWritePages	dd ?
CcDataFlushes		dd ?
CcDataPages		dd ?
ContextSwitches		dd ?
FirstLevelTbFills	dd ?
SecondLevelTbFills	dd ?
SystemCalls		dd ?
CcTotalDirtyPages	dq ?
CcDirtyPageThreshold	dq ?
ResidentAvailablePages	LONG64 ?
SharedCommittedPages	dq ?
MINIDUMP_SYSTEM_PERFORMANCE_INFORMATION ends
PMINIDUMP_SYSTEM_PERFORMANCE_INFORMATION typedef ptr MINIDUMP_SYSTEM_PERFORMANCE_INFORMATION

define MINIDUMP_SYSMEMINFO1_FILECACHE_TRANSITIONREPURPOSECOUNT_FLAGS	  0x0001
define MINIDUMP_SYSMEMINFO1_BASICPERF					  0x0002
define MINIDUMP_SYSMEMINFO1_PERF_CCTOTALDIRTYPAGES_CCDIRTYPAGETHRESHOLD	  0x0004
define MINIDUMP_SYSMEMINFO1_PERF_RESIDENTAVAILABLEPAGES_SHAREDCOMMITPAGES 0x0008

MINIDUMP_SYSTEM_MEMORY_INFO_1 struct
Revision		dw ?
Flags			dw ?
BasicInfo		MINIDUMP_SYSTEM_BASIC_INFORMATION <>
FileCacheInfo		MINIDUMP_SYSTEM_FILECACHE_INFORMATION <>
BasicPerfInfo		MINIDUMP_SYSTEM_BASIC_PERFORMANCE_INFORMATION <>
PerfInfo		MINIDUMP_SYSTEM_PERFORMANCE_INFORMATION <>
MINIDUMP_SYSTEM_MEMORY_INFO_1 ends
PMINIDUMP_SYSTEM_MEMORY_INFO_1 typedef ptr MINIDUMP_SYSTEM_MEMORY_INFO_1

MINIDUMP_SYSTEM_MEMORY_INFO_N typedef MINIDUMP_SYSTEM_MEMORY_INFO_1
PMINIDUMP_SYSTEM_MEMORY_INFO_N typedef ptr MINIDUMP_SYSTEM_MEMORY_INFO_N

MINIDUMP_PROCESS_VM_COUNTERS_1 struct
Revision		dw ?
PageFaultCount		dd ?
PeakWorkingSetSize	dq ?
WorkingSetSize		dq ?
QuotaPeakPagedPoolUsage dq ?
QuotaPagedPoolUsage	dq ?
QuotaPeakNonPagedPoolUsage dq ?
QuotaNonPagedPoolUsage	dq ?
PagefileUsage		dq ?
PeakPagefileUsage	dq ?
PrivateUsage		dq ?
MINIDUMP_PROCESS_VM_COUNTERS_1 ends
PMINIDUMP_PROCESS_VM_COUNTERS_1 typedef ptr MINIDUMP_PROCESS_VM_COUNTERS_1

define MINIDUMP_PROCESS_VM_COUNTERS		   0x0001
define MINIDUMP_PROCESS_VM_COUNTERS_VIRTUALSIZE	   0x0002
define MINIDUMP_PROCESS_VM_COUNTERS_EX		   0x0004
define MINIDUMP_PROCESS_VM_COUNTERS_EX2		   0x0008
define MINIDUMP_PROCESS_VM_COUNTERS_JOB		   0x0010

MINIDUMP_PROCESS_VM_COUNTERS_2 struct
Revision		dw ?
Flags			dw ?
PageFaultCount		dd ?
PeakWorkingSetSize	dq ?
WorkingSetSize		dq ?
QuotaPeakPagedPoolUsage dq ?
QuotaPagedPoolUsage	dq ?
QuotaPeakNonPagedPoolUsage dq ?
QuotaNonPagedPoolUsage	dq ?
PagefileUsage		dq ?
PeakPagefileUsage	dq ?
PeakVirtualSize		dq ?
VirtualSize		dq ?
PrivateUsage		dq ?
PrivateWorkingSetSize	dq ?
SharedCommitUsage	dq ?
JobSharedCommitUsage	dq ?
JobPrivateCommitUsage	dq ?
JobPeakPrivateCommitUsage dq ?
JobPrivateCommitLimit	dq ?
JobTotalCommitLimit	dq ?
MINIDUMP_PROCESS_VM_COUNTERS_2 ends
PMINIDUMP_PROCESS_VM_COUNTERS_2 typedef ptr MINIDUMP_PROCESS_VM_COUNTERS_2

MINIDUMP_PROCESS_VM_COUNTERS_N typedef MINIDUMP_PROCESS_VM_COUNTERS_2
PMINIDUMP_PROCESS_VM_COUNTERS_N typedef ptr MINIDUMP_PROCESS_VM_COUNTERS_N

MINIDUMP_USER_RECORD	struct
Type			dd ?
Memory			MINIDUMP_LOCATION_DESCRIPTOR <>
MINIDUMP_USER_RECORD	ends
PMINIDUMP_USER_RECORD	typedef ptr MINIDUMP_USER_RECORD

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_GAMES)

MINIDUMP_USER_STREAM	struct
Type			dd ?
BufferSize		dd ?
Buffer			PVOID ?
MINIDUMP_USER_STREAM	ends
PMINIDUMP_USER_STREAM	typedef ptr MINIDUMP_USER_STREAM

MINIDUMP_USER_STREAM_INFORMATION struct
UserStreamCount		dd ?
UserStreamArray		PMINIDUMP_USER_STREAM ?
MINIDUMP_USER_STREAM_INFORMATION ends
PMINIDUMP_USER_STREAM_INFORMATION typedef ptr MINIDUMP_USER_STREAM_INFORMATION

.enum MINIDUMP_CALLBACK_TYPE {
    ModuleCallback,
    ThreadCallback,
    ThreadExCallback,
    IncludeThreadCallback,
    IncludeModuleCallback,
    MemoryCallback,
    CancelCallback,
    WriteKernelMinidumpCallback,
    KernelMinidumpStatusCallback,
    RemoveMemoryCallback,
    IncludeVmRegionCallback,
    IoStartCallback,
    IoWriteAllCallback,
    IoFinishCallback,
    ReadMemoryFailureCallback,
    SecondaryFlagsCallback,
    IsProcessSnapshotCallback,
    VmStartCallback,
    VmQueryCallback,
    VmPreReadCallback,
    VmPostReadCallback
    }

MINIDUMP_THREAD_CALLBACK struct
ThreadId		dd ?
ThreadHandle		HANDLE ?
if defined(_ARM64_)
Pad			dd ?
endif
Context			CONTEXT <>
SizeOfContext		dd ?
StackBase		dq ?
StackEnd		dq ?
MINIDUMP_THREAD_CALLBACK ends
PMINIDUMP_THREAD_CALLBACK typedef ptr MINIDUMP_THREAD_CALLBACK

MINIDUMP_THREAD_EX_CALLBACK struct
ThreadId		dd ?
ThreadHandle		HANDLE ?
if defined(_ARM64_)
Pad			dd ?
endif
Context			CONTEXT <>
SizeOfContext		dd ?
StackBase		dq ?
StackEnd		dq ?
BackingStoreBase	dq ?
BackingStoreEnd		dq ?
MINIDUMP_THREAD_EX_CALLBACK ends
PMINIDUMP_THREAD_EX_CALLBACK typedef ptr MINIDUMP_THREAD_EX_CALLBACK

MINIDUMP_INCLUDE_THREAD_CALLBACK struct
ThreadId		dd ?
MINIDUMP_INCLUDE_THREAD_CALLBACK ends
PMINIDUMP_INCLUDE_THREAD_CALLBACK typedef ptr MINIDUMP_INCLUDE_THREAD_CALLBACK

.enum THREAD_WRITE_FLAGS {
    ThreadWriteThread		 = 0x0001,
    ThreadWriteStack		 = 0x0002,
    ThreadWriteContext		 = 0x0004,
    ThreadWriteBackingStore	 = 0x0008,
    ThreadWriteInstructionWindow = 0x0010,
    ThreadWriteThreadData	 = 0x0020,
    ThreadWriteThreadInfo	 = 0x0040,
    }

MINIDUMP_MODULE_CALLBACK struct
FullPath		PWCHAR ?
BaseOfImage		dq ?
SizeOfImage		dd ?
CheckSum		dd ?
TimeDateStamp		dd ?
VersionInfo		VS_FIXEDFILEINFO <>
CvRecord		PVOID ?
SizeOfCvRecord		dd ?
MiscRecord		PVOID ?
SizeOfMiscRecord	dd ?
MINIDUMP_MODULE_CALLBACK ends
PMINIDUMP_MODULE_CALLBACK typedef ptr MINIDUMP_MODULE_CALLBACK

MINIDUMP_INCLUDE_MODULE_CALLBACK struct
BaseOfImage		dq ?
MINIDUMP_INCLUDE_MODULE_CALLBACK ends
PMINIDUMP_INCLUDE_MODULE_CALLBACK typedef ptr MINIDUMP_INCLUDE_MODULE_CALLBACK

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.enum MODULE_WRITE_FLAGS {
    ModuleWriteModule	     = 0x0001,
    ModuleWriteDataSeg	     = 0x0002,
    ModuleWriteMiscRecord    = 0x0004,
    ModuleWriteCvRecord	     = 0x0008,
    ModuleReferencedByMemory = 0x0010,
    ModuleWriteTlsData	     = 0x0020,
    ModuleWriteCodeSegs	     = 0x0040,
    }

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_GAMES)

MINIDUMP_IO_CALLBACK	struct
Handle			HANDLE ?
_Offset			dq ?
Buffer			PVOID ?
BufferBytes		dd ?
MINIDUMP_IO_CALLBACK	ends
PMINIDUMP_IO_CALLBACK	typedef ptr MINIDUMP_IO_CALLBACK

MINIDUMP_READ_MEMORY_FAILURE_CALLBACK struct
_Offset			dq ?
Bytes			dd ?
FailureStatus		HRESULT ?
MINIDUMP_READ_MEMORY_FAILURE_CALLBACK ends
PMINIDUMP_READ_MEMORY_FAILURE_CALLBACK typedef ptr MINIDUMP_READ_MEMORY_FAILURE_CALLBACK

MINIDUMP_VM_QUERY_CALLBACK struct
_Offset			dq ?
MINIDUMP_VM_QUERY_CALLBACK ends
PMINIDUMP_VM_QUERY_CALLBACK typedef ptr MINIDUMP_VM_QUERY_CALLBACK

MINIDUMP_VM_PRE_READ_CALLBACK struct
_Offset			dq ?
Buffer			PVOID ?
Size			dd ?
MINIDUMP_VM_PRE_READ_CALLBACK ends
PMINIDUMP_VM_PRE_READ_CALLBACK typedef ptr MINIDUMP_VM_PRE_READ_CALLBACK

MINIDUMP_VM_POST_READ_CALLBACK struct
_Offset			dq ?
Buffer			PVOID ?
Size			dd ?
Completed		dd ?
Status			HRESULT ?
MINIDUMP_VM_POST_READ_CALLBACK ends
PMINIDUMP_VM_POST_READ_CALLBACK typedef ptr MINIDUMP_VM_POST_READ_CALLBACK

MINIDUMP_CALLBACK_INPUT struct
ProcessId		dd ?
ProcessHandle		HANDLE ?
CallbackType		dd ?
union
 Status			HRESULT ?
 Thread			MINIDUMP_THREAD_CALLBACK <>
 ThreadEx		MINIDUMP_THREAD_EX_CALLBACK <>
 Module			MINIDUMP_MODULE_CALLBACK <>
 IncludeThread		MINIDUMP_INCLUDE_THREAD_CALLBACK <>
 IncludeModule		MINIDUMP_INCLUDE_MODULE_CALLBACK <>
 Io			MINIDUMP_IO_CALLBACK <>
 ReadMemoryFailure	MINIDUMP_READ_MEMORY_FAILURE_CALLBACK <>
 SecondaryFlags		dd ?
 VmQuery		MINIDUMP_VM_QUERY_CALLBACK <>
 VmPreRead		MINIDUMP_VM_PRE_READ_CALLBACK <>
 VmPostRead		MINIDUMP_VM_POST_READ_CALLBACK <>
ends
MINIDUMP_CALLBACK_INPUT ends
PMINIDUMP_CALLBACK_INPUT typedef ptr MINIDUMP_CALLBACK_INPUT

MINIDUMP_CALLBACK_OUTPUT struct
union
 ModuleWriteFlags	dd ?
 ThreadWriteFlags	dd ?
 SecondaryFlags		dd ?
 struct
  MemoryBase		dq ?
  MemorySize		dd ?
 ends
 struct
  CheckCancel		BOOL ?
  Cancel		BOOL ?
 ends
 Handle			HANDLE ?
 struct
  VmRegion		MINIDUMP_MEMORY_INFO <>
  Continue		BOOL ?
 ends
 struct
  VmQueryStatus		HRESULT ?
  VmQueryResult		MINIDUMP_MEMORY_INFO <>
 ends
 struct
  VmReadStatus		HRESULT ?
  VmReadBytesCompleted	dd ?
 ends
 Status			HRESULT ?
ends
MINIDUMP_CALLBACK_OUTPUT ends
PMINIDUMP_CALLBACK_OUTPUT typedef ptr MINIDUMP_CALLBACK_OUTPUT

.enum MINIDUMP_TYPE {
    MiniDumpNormal			   = 0x00000000,
    MiniDumpWithDataSegs		   = 0x00000001,
    MiniDumpWithFullMemory		   = 0x00000002,
    MiniDumpWithHandleData		   = 0x00000004,
    MiniDumpFilterMemory		   = 0x00000008,
    MiniDumpScanMemory			   = 0x00000010,
    MiniDumpWithUnloadedModules		   = 0x00000020,
    MiniDumpWithIndirectlyReferencedMemory = 0x00000040,
    MiniDumpFilterModulePaths		   = 0x00000080,
    MiniDumpWithProcessThreadData	   = 0x00000100,
    MiniDumpWithPrivateReadWriteMemory	   = 0x00000200,
    MiniDumpWithoutOptionalData		   = 0x00000400,
    MiniDumpWithFullMemoryInfo		   = 0x00000800,
    MiniDumpWithThreadInfo		   = 0x00001000,
    MiniDumpWithCodeSegs		   = 0x00002000,
    MiniDumpWithoutAuxiliaryState	   = 0x00004000,
    MiniDumpWithFullAuxiliaryState	   = 0x00008000,
    MiniDumpWithPrivateWriteCopyMemory	   = 0x00010000,
    MiniDumpIgnoreInaccessibleMemory	   = 0x00020000,
    MiniDumpWithTokenInformation	   = 0x00040000,
    MiniDumpWithModuleHeaders		   = 0x00080000,
    MiniDumpFilterTriage		   = 0x00100000,
    MiniDumpWithAvxXStateContext	   = 0x00200000,
    MiniDumpWithIptTrace		   = 0x00400000,
    MiniDumpScanInaccessiblePartialPages   = 0x00800000,
    MiniDumpFilterWriteCombinedMemory	   = 0x01000000,
    MiniDumpValidTypeFlags		   = 0x01ffffff,
    }

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.enum MINIDUMP_SECONDARY_FLAGS {
    MiniSecondaryWithoutPowerInfo = 0x00000001,
    MiniSecondaryValidFlags	  = 0x00000001,
    }

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_GAMES)

CALLBACK(MINIDUMP_CALLBACK_ROUTINE, :ptr, :PMINIDUMP_CALLBACK_INPUT, :PMINIDUMP_CALLBACK_OUTPUT)

MINIDUMP_CALLBACK_INFORMATION struct
CallbackRoutine		MINIDUMP_CALLBACK_ROUTINE ?
CallbackParam		PVOID ?
MINIDUMP_CALLBACK_INFORMATION ends
PMINIDUMP_CALLBACK_INFORMATION typedef ptr MINIDUMP_CALLBACK_INFORMATION

RVA_TO_ADDR macro Mapping,Rva
  exitm<((Mapping) + (Rva))>
  endm

MiniDumpWriteDump proto WINAPI :HANDLE, :DWORD, :HANDLE, :MINIDUMP_TYPE, :PMINIDUMP_EXCEPTION_INFORMATION, :PMINIDUMP_USER_STREAM_INFORMATION, :PMINIDUMP_CALLBACK_INFORMATION

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
MiniDumpReadDumpStream proto WINAPI :ptr, :DWORD, :ptr, :ptr, :ptr
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_GAMES)
.pragma pack(pop)
endif

endif
